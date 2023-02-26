#include "weight.h"
#include "ui_weight.h"
#include <QMessageBox>

extern QPair<double, double> range;

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
        range.first = stod(ui->lineEdit_begin->text().toStdString());
        range.second = stod(ui->lineEdit_end->text().toStdString());
        window()->close();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неверный вес");
        ui->lineEdit_begin->clear();
        ui->lineEdit_end->clear();
    }
}

