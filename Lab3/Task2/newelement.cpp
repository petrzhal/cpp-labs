#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "newelement.h"
#include "ui_newelement.h"
#include "../../Lib/Vector/vector.h"
#include "pair.cpp"

extern vector<int> firstNew;
extern vector<pair<int, double>> secondNew;
extern bool isNewAdded;
extern bool isNewAdded2;

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
        isNewAdded = true;
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод");
        ui->lineEdit->clear();
        isNewAdded = false;
    }
}


void NewElement::on_pushButton_add_2_clicked()
{
    try {
        secondNew.push_back(make_pair(stoi(ui->lineEdit_2->text().toStdString()), stod(ui->lineEdit_3->text().toStdString())));
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        isNewAdded2 = true;
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        isNewAdded2 = false;
    }
}


void NewElement::on_pushButton_clicked()
{
    window()->close();
}

