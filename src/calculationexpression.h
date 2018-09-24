#ifndef CALCULATIONEXPRESSION_H
#define CALCULATIONEXPRESSION_H

#include <QObject>

class CalculationExpression : public QObject
{
    Q_OBJECT
    enum NUMBER_TYPE{
        DATA_INT,
        DATA_DOUBLE,
        DATA_UNDEFINED,
    };
public:
    explicit CalculationExpression(QObject *parent = nullptr);

    Q_INVOKABLE QString getValue(QString expression, QString ansValue);

private:
    bool getExpressionList(QString expression, QString ansValue, QStringList &list, QString & error);
    bool getExpressionValue(QStringList &list,QString &vlaue, QString &error);
    bool getCurrentValue(QString &arg1, QString &arg2, QString &symbol, QString &result, QString &error);
    bool getNumber(QString &c, NUMBER_TYPE &type, int &intValue, double &doubleValue);
    bool isNumber(const QString &c);
    bool isBaseSymbol(const QString &c);
    bool isMulOrDivSymbol(const QString &symbol);
    bool isAddOrSubSymbol(const QString &symbol);

private:
    const QString m_error1;
    const QString m_error2;
    const QString m_error3;
};

#endif // CALCULATIONEXPRESSION_H
