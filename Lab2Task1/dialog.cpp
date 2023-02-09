#include "dialog.h"
#include "ui_dialog.h"
#include "abiturient.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Введите данные\nдобавляемого абитуриента");
    this->setWindowTitle("Добавление");
}

Dialog::Dialog(const abiturient& ab) :
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText("Введите данные\nизменяемого абитуриента");
    this->setWindowTitle("Изменение");
    ui->lineEdit->setText(ab.get_name());
    ui->lineEdit_2->setText(QString::number(ab.get_rus()));
    ui->lineEdit_3->setText(QString::number(ab.get_math()));
    ui->lineEdit_4->setText(QString::number(ab.get_phys()));
}

Dialog::~Dialog()
{
    delete ui;
}
