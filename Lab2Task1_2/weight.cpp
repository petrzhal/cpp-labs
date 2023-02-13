#include "weight.h"
#include "ui_weight.h"
#include <QMessageBox>

extern QPair<int, int> range;

Weight::Weight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Weight)
{
    ui->setupUi(this);
    this->setWindowTitle("Определение весовой категории");
}

Weight::~Weight()
{
    delete ui;
}

void Weight::on_pushButton_confirm_clicked()
{
    try {
        range.first = ui->lineEdit_begin->text().toInt();
        range.second = ui->lineEdit_end->text().toInt();
        window()->close();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неверный вес");
        ui->lineEdit_begin->clear();
        ui->lineEdit_end->clear();
    }
}

