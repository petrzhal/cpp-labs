#include "expression.h"
#include "stack.cpp"
#include <QDebug>
#include <algorithm>

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

Expression::Expression(const QString& expr)
{
    infix = expr;
    QString res;
    stack<QChar> operators;
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i].isLetter()) {
            res.push_back(expr[i]);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            if (!operators.size()) {
                operators.push(expr[i]);
            }
            else {
                while ((Prioritization(expr[i]) <= Prioritization(operators.top()))) {
                    res.push_back(operators.top());
                    operators.pop();
                    if (!operators.size())
                        break;
                }
                operators.push(expr[i]);
            }
        }
        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (operators.top() != '(') {
                res.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
    }
    qDebug() << res;
    while (operators.size()) {
        res.push_back(operators.top());
        operators.pop();
    }
    postfix = res;
}

double Expression::Evaluate(double a, double b, double c, double d, double e) {
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

QString Expression::PostfixForm() {
    return postfix;
}
