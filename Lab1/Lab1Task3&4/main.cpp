#include <iostream>
#include "Expression.cpp"

int main() {
    Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(3));
    Expression* expr = new BinaryOperation(new Number(6), '+', sube);
    std::cout << expr->evaluate() << "\n";
    std::cout << check_equals(expr, new Number(4.5)) << "\n";
    delete expr;
    system("pause");    
}
