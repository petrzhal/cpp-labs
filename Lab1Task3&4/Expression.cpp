#include <iostream>

class Expression {
public:
    virtual double evaluate() = 0;
    virtual ~Expression() = default;
};

class Number : public Expression {
    double number;
public:
    explicit Number(double num) : Expression() {
        number = num;
    }

    double evaluate() override {
        return number;
    }
};

class BinaryOperation : public Expression {
protected:
    Expression* left;
    Expression* right;
    char op;
public:
    ~BinaryOperation() override {
        delete left;
        delete right;
    }

    BinaryOperation(Expression* exp1, char op, Expression* exp2) : Expression() {
        left = exp1;
        right = exp2;
        this->op = op;
    }
    double evaluate() override {
        if (op == '*')
            return left->evaluate() * right->evaluate();
        else if (op == '+')
            return left->evaluate() + right->evaluate();
        else if (op == '-')
            return left->evaluate() - right->evaluate();
        else if (op == '/')
            return left->evaluate() / right->evaluate();
    }
};

bool check_equals(Expression const* left, Expression const* right) {
    return (*((size_t*)left) == *((size_t*)right));
}