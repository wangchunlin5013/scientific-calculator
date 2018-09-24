#ifndef CALCULATIONEXPRESSION_H
#define CALCULATIONEXPRESSION_H

#include <QObject>

class CalculationExpression : public QObject
{
    Q_OBJECT
public:
    explicit CalculationExpression(QObject *parent = nullptr);

    Q_INVOKABLE QString getValue(QString expression, QString ansValue);

signals:

public slots:
};

#endif // CALCULATIONEXPRESSION_H
