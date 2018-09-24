#include "calculationexpression.h"

CalculationExpression::CalculationExpression(QObject *parent) : QObject(parent)
{

}

QString CalculationExpression::getValue(QString expression, QString ansValue)
{
    return expression + ansValue;
}
