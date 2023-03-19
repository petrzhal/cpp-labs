#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "newelement.h"
#include "ui_newelement.h"
#include "vector.cpp"
#include "pair.cpp"

extern vector<int> firstNew;
extern vector<pair<int, double>> secondNew;
extern bool isNewAdded;

NewElement::NewElement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewElement)
{
    ui->setupUi(this);
    firstNew.clear();
    secondNew.clear();
}

NewElement::~NewElement()
{
    delete ui;
}

void NewElement::on_pushButton_add_clicked()
{
    try {
        firstNew.push_back(stoi(ui->lineEdit->text().toStdString()));
        ui->lineEdit->clear();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод");
        ui->lineEdit->clear();
    }
}


void NewElement::on_pushButton_add_2_clicked()
{
    try {
        secondNew.push_back(make_pair(stoi(ui->lineEdit_2->text().toStdString()), stod(ui->lineEdit_3->text().toStdString())));
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
}


void NewElement::on_pushButton_clicked()
{
    window()->close();
}

