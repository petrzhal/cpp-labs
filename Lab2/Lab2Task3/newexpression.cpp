#include "newexpression.h"
#include "ui_newexpression.h"
#include <QMessageBox>

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

NewExpression::~NewExpression()
{
    delete ui;
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
        window()->close();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        checked = false;
    }
}

