#include "calculationexpression.h"
#include <QStringList>

CalculationExpression::CalculationExpression(QObject *parent)
    : QObject(parent)
    , m_error1(QString("Syntax ERROR"))
    , m_error2(QString("Match ERROR"))
    , m_error3(QString("Unknown ERROR"))
{

}

QString CalculationExpression::getValue(QString expression, QString ansValue)
{
    if(expression.isEmpty())
        return QString("0");

    QStringList list;
    QString error;
    bool isSuccess = getExpressionList(expression, ansValue, list, error);
    if(!isSuccess)
        return error;

    QString value;
    isSuccess = getExpressionValue(list, value, error);
    if(!isSuccess)
        return error;

    return value;
}



bool CalculationExpression::getExpressionList(QString expression, QString ansValue, QStringList &list, QString &error)
{
    //处理Ans
    expression.replace(QString("Ans"), ansValue);

    //处理E
    if(expression.contains(QString("E")))
    {

    }

    QString number;
    for(int i=0; i< expression.count(); ++i)
    {
        QString c = expression.at(i);
        if(isNumber(c))
        {
            //转换成功则将数字连接
            number = number + c;
        }
        else if(c == QString("."))
        {
            //如果一个数字中包含不只一个.则返回错误
            if(number.contains("."))
            {
                error = m_error1;
                return false;
            }
            else
            {
                number = number + c;
            }
        }
        else
        {   //转换失败则说明为符号===========先只考虑加减乘除，以后添加E和Ans
            if(isBaseSymbol(c))
            {
                //先将数字缓存
                if(!number.isEmpty())
                {
                    list << number;
                    number.clear();
                }
                else if(i == 0)
                {
                    //如果整个表达式中第一个就是基本符号，则自动在前面加一个数字0
                    list << QString("0");
                }
                else
                {
                    error  = m_error1;
                    return false;
                }

                //再将符号缓存
                list << c;
            }
        }
    }

    if(!number.isEmpty())
    {
        //表达式最后的数字
        list << number;
    }

    return true;
}

bool CalculationExpression::getExpressionValue(QStringList &list, QString &value, QString &error)
{
    QStringList removedMulAndDivList;
    //计算乘法和除法
    int expressionCount = list.count();
    for(int i=0; i< expressionCount; ++i)
    {
        QString expression = list.at(i);
        if(isMulOrDivSymbol(expression))
        {
            if(i == expressionCount - 1)
            {
                //如果最后一个是符号，则返回错误
                error = m_error1;
                return false;
            }

            //取出该符号位的前一个数字和后一个数字进行计算
            //符号位前、后必然是数字（在getExpressionList中已经将小数点、符号位相邻情况进行处理）
            QString frontNumber = removedMulAndDivList.last();
            QString afterNumber = list.at(i + 1);
            QString currentSymbol = list.at(i);
            QString result;
            bool isSuccess = getCurrentValue(frontNumber, afterNumber, currentSymbol, result, error);
            if(!isSuccess)
            {
                return false;
            }

            //下一项已被取出来使用
            ++i;

            //使用计算结果替换新列表中的最后一项
            removedMulAndDivList.last() = result;
        }
        else
        {
            removedMulAndDivList << expression;
        }
    }

    //计算加法减法
    QStringList removedAddAndSubList;
    expressionCount = removedMulAndDivList.count();
    for(int i=0; i< expressionCount; ++i)
    {
        QString expression = removedMulAndDivList.at(i);
        if(isAddOrSubSymbol(expression))
        {
            if(i == expressionCount - 1)
            {
                //如果最后一个是符号，则返回错误
                error = m_error1;
                return false;
            }

            //取出该符号位的前一个数字和后一个数字进行计算
            //符号位前、后必然是数字（在getExpressionList中已经将小数点、符号位相邻情况进行处理）
            QString frontNumber = removedAddAndSubList.last();
            QString afterNumber = removedMulAndDivList.at(i + 1);
            QString currentSymbol = removedMulAndDivList.at(i);
            QString result;
            bool isSuccess = getCurrentValue(frontNumber, afterNumber, currentSymbol, result, error);
            if(!isSuccess)
            {
                return false;
            }

            //下一项已被取出来使用
            ++i;

            //使用计算结果替换新列表中的最后一项
            removedAddAndSubList.last() = result;
        }
        else
        {
            removedAddAndSubList << expression;
        }
    }

    //理论上removedAddAndSubList只有最后一个计算结果了
    if(removedAddAndSubList.count() != 1)
    {
        error = m_error1;
        return false;
    }

    value = removedAddAndSubList.at(0);
    return true;
}

bool CalculationExpression::getCurrentValue(QString &arg1, QString &arg2, QString &symbol, QString &result, QString &error)
{
    if(!isNumber(arg1) || !isNumber(arg2))
    {
        error = m_error1;
        return false;
    }

//    bool isDouble = false;
//    if(arg1.contains(QString(".")) || arg2.contains(QString(".")))
//    {
//        isDouble = true;
//    }
    if(symbol == QString("+"))
    {
        result = QString::number(arg1.toDouble() + arg2.toDouble());
    }
    else if(symbol == QString("-"))
    {
        result = QString::number(arg1.toDouble() - arg2.toDouble());
    }
    else if(symbol == QString("X"))
    {
        result = QString::number(arg1.toDouble() * arg2.toDouble());
    }
    else if(symbol == QString("÷"))
    {
        if(arg2 == QString("0"))
        {
            error = m_error2;
            return false;
        }
        result = QString::number(arg1.toDouble() / arg2.toDouble());
    }
    else
    {
        error = m_error1;
        return false;
    }

    return true;
}

bool CalculationExpression::getNumber(QString &c, CalculationExpression::NUMBER_TYPE &type, int &intValue, double &doubleValue)
{
    bool okInt = false;
    bool okDouble = false;

    intValue = c.toInt(&okInt);
    if(okInt)
    {
        type = DATA_INT;
        return true;
    }

    doubleValue = c.toDouble(&okDouble);
    if(okDouble)
    {
        type = DATA_DOUBLE;
        return true;
    }

    return false;
}

bool CalculationExpression::isNumber(const QString &c)
{
    bool okInt = false;
    bool okDouble = false;

    c.toInt(&okInt);
    if(okInt)
    {
        return true;
    }

    c.toDouble(&okDouble);
    if(okDouble)
    {
        return true;
    }

    return false;
}

bool CalculationExpression::isBaseSymbol(const QString &c)
{
    if(c == QString("+") || c == QString("-") || c == QString("X") || c == QString("÷"))
        return true;
    return false;
}

bool CalculationExpression::isMulOrDivSymbol(const QString &symbol)
{
    if(symbol == QString("X") || symbol == QString("÷"))
        return true;
    return false;
}

bool CalculationExpression::isAddOrSubSymbol(const QString &symbol)
{
    if(symbol == QString("+") || symbol == QString("-"))
        return true;
    return false;
}
