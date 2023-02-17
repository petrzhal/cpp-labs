#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <QString>

class Expression
{
private:
    QString infix;
    QString postfix;
public:
    Expression(const QString&);
    QString PostfixForm();
    double Evaluate(double a, double b, double c, double d, double e);
};

#endif // EXPRESSION_H
