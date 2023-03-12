#include "newexpression.h"
#include "ui_newexpression.h"
#include <QMessageBox>
#include <QStack>
#include "stack.cpp"

extern QString newExpr;
extern double abcde[5];
extern bool checked;

NewExpression::NewExpression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewExpression)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление выражения");
}

NewExpression::NewExpression(Expression& expr) :
    ui(new Ui::NewExpression)
{
    ui->setupUi(this);
    this->setWindowTitle("Изменение выражения");
    ui->lineEdit_a->setText(QString::number(expr.get_a()));
    ui->lineEdit_b->setText(QString::number(expr.get_b()));
    ui->lineEdit_c->setText(QString::number(expr.get_c()));
    ui->lineEdit_d->setText(QString::number(expr.get_d()));
    ui->lineEdit_e->setText(QString::number(expr.get_e()));
    ui->lineEdit->setText(expr.get_infix());
}

NewExpression::~NewExpression()
{
    delete ui;
}

bool cmp(int a, int b) {
    if (a && !b)
        return true;
    else if (!a && b)
        return false;
    else if (a < b)
        return true;
    else
        return false;
}

QPair<int, int> Bracketscorrect(const QString& str) {
    stack<int> stackFigure;
    stack<int> stackSquare;
    stack<int> stackRound;
    char figL = '{', figR = '}';
    char sqrL = '[', sqrR = ']';
    char rndL = '(', rndR = ')';

    int indFigure;
    int indSquare;
    int indRound;
    bool err1 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == figL)
            stackFigure.push(i);
        else if (str[i] == figR) {
            if (stackFigure.size() > 0)
                stackFigure.pop();
            else {
                indFigure =  i + 1;
                err1 = true;
                break;
            }
        }
    }
    if (!err1 && stackFigure.size() > 0) {
        while (stackFigure.size() != 1) {
            stackFigure.pop();
        }
        indFigure =  stackFigure.top() + 1;
    }
    else if (!err1) {
        indFigure = 0;
    }

    bool err2 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == sqrL)
            stackSquare.push(i);
        else if (str[i] == sqrR) {
            if (stackSquare.size() > 0)
                stackSquare.pop();
            else {
                indSquare =  i + 1;
                err2 = true;
                break;
            }
        }
    }
    if (!err2 && stackSquare.size() > 0) {
        while (stackSquare.size() != 1) {
            stackSquare.pop();
        }
        indSquare =  stackSquare.top() + 1;
    }
    else if (!err2) {
        indSquare = 0;
    }
    bool err3 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == rndL)
            stackRound.push(i);
        else if (str[i] == rndR) {
            if (stackRound.size() > 0)
                stackRound.pop();
            else {
                indRound =  i + 1;
                err3 = true;
                break;
            }
        }
    }
    if (!err3 && stackRound.size() > 0) {
        while (stackRound.size() != 1) {
            stackRound.pop();
        }
        indRound = stackRound.top() + 1;
    }
    else if (!err3) {
        indRound = 0;
    }

    int res;
    if (indFigure && indRound && indSquare) {
        res = 0;
    }
    else {
        res = std::min(std::min(indFigure, indRound, cmp), indSquare, cmp);
    }

    int row = 1;
    int col = 0;
    QPair<int, int> pos;
    for (int i = 0; i < res; ++i) {
        if (str[i] == '\n') {
            row++;
            col = 0;
        }
        else col++;
        pos.first = row;
        pos.second = col;
    }
    return pos;
}

void NewExpression::on_pushButton_clicked()
{
    try {
        QString expr = ui->lineEdit->text();
        for (const auto& ch : expr) {
            if (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'e' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ')' && ch != '(') {
                throw "Invalid expression";
            }
        }
        newExpr = ui->lineEdit->text();
        abcde[0] = stod(ui->lineEdit_a->text().toStdString());
        abcde[1] = stod(ui->lineEdit_b->text().toStdString());
        abcde[2] = stod(ui->lineEdit_c->text().toStdString());
        abcde[3] = stod(ui->lineEdit_d->text().toStdString());
        abcde[4] = stod(ui->lineEdit_e->text().toStdString());
        checked = true;
        QPair<int, int> brackets = Bracketscorrect(newExpr);
        if (brackets.first || brackets.second) {
            QMessageBox::critical(this, "Ошибка", "В выражении неправильно расставлены скобки");
        }
        else {
            window()->close();
        }
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        checked = false;
    }
}

