#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <QString>

class Expression
{
private:
    QString infix;
    QString postfix;
    double a;
    double b;
    double c;
    double d;
    double e;
    QString PostfixForm();
public:
    Expression();
    Expression(const QString&);
    QString get_postfix() const;
    QString get_infix() const;
    void set_infix(const QString&);
    double evaluate();
    void set_values(double a, double b, double c, double d, double e);
    double get_a() const;
    double get_b() const;
    double get_c() const;
    double get_d() const;
    double get_e() const;
};

void GetTests();

#endif // EXPRESSION_H
