#include "expression.h"
#include "stack.cpp"
#include <QDebug>
#include <algorithm>
#include <QFile>
#include <QTextStream>

extern QVector<Expression> tests;

int Prioritization(const QChar& ch) {
    if (ch == '*' || ch == '/')
        return 3;
    else if (ch == '+' || ch == '-')
        return 2;
    else if (ch == '(')
        return 1;
    else
        return 0;
}

Expression::Expression()
{
    a = b = c = d = e = 0;
}

Expression::Expression(const QString& expr)
{
    infix = expr;    
    postfix = PostfixForm();
}

QString Expression::get_postfix() const
{
    return postfix;
}

QString Expression::get_infix() const
{
    return infix;
}

double Expression::evaluate() {
    stack<double> stack;
    for (int i = 0; i < postfix.length(); ++i) {
        if (postfix[i] == 'a')
            stack.push(a);
        else if (postfix[i] == 'b')
            stack.push(b);
        else if (postfix[i] == 'c')
            stack.push(c);
        else if (postfix[i] == 'd')
            stack.push(d);
        else if (postfix[i] == 'e')
            stack.push(e);
        else if (postfix[i] == '+') {
            double n1 = stack.top();
            stack.pop();
            double n2 = stack.top();
            stack.pop();
            stack.push(n1 + n2);
        }
        else if (postfix[i] == '-') {
            double n1 = stack.top();
            stack.pop();
            double n2 = stack.top();
            stack.pop();
            stack.push(n2 - n1);
        }
        else if (postfix[i] == '*') {
            double n1 = stack.top();
            stack.pop();
            double n2 = stack.top();
            stack.pop();
            stack.push(n1 * n2);
        }
        else if (postfix[i] == '/') {
            double n1 = stack.top();
            stack.pop();
            double n2 = stack.top();
            stack.pop();
            stack.push(n2 / n1);
        }
    }
    return stack.top();
}

void Expression::set_values(double a, double b, double c, double d, double e) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
}

double Expression::get_a() const
{
    return a;
}

double Expression::get_b() const
{
    return b;
}

double Expression::get_c() const
{
    return c;
}

double Expression::get_d() const
{
    return d;
}

double Expression::get_e() const
{
    return e;
}

QString Expression::PostfixForm() {
    QString res;
    stack<QChar> operators;
    for (int i = 0; i < infix.length(); ++i) {
        if (infix[i].isLetter()) {
            res.push_back(infix[i]);
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            if (!operators.size()) {
                operators.push(infix[i]);
            }
            else {
                while ((Prioritization(infix[i]) <= Prioritization(operators.top()))) {
                    res.push_back(operators.top());
                    operators.pop();
                    if (!operators.size())
                        break;
                }
                operators.push(infix[i]);
            }
        }
        else if (infix[i] == '(') {
            operators.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (operators.top() != '(') {
                res.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
    }
    while (operators.size()) {
        res.push_back(operators.top());
        operators.pop();
    }
    return res;
}

void Expression::set_infix(const QString& infix)
{
    this->infix = infix;
    this->postfix = PostfixForm();
}

void GetTests() {
    QFile f("F:/tests.txt");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file(&f);
    int i = 0;
    while (!file.atEnd()) {
        Expression expr;
        QString str;
        file.readLineInto(&str);
        expr.set_infix(str);
        double a, b, c, d, e;
        file >> a >> b >> c >> d >> e;
        expr.set_values(a, b, c, d, e);
        tests.push_back(expr);
        file.readLineInto(&str);
    }
    f.close();
}
