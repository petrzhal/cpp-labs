#include "resize.h"
#include "ui_resize.h"
#include <QMessageBox>

extern int newSize;
extern int value;
extern bool sizeEntered;

Resize::Resize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resize)
{
    ui->setupUi(this);
    this->setWindowTitle("Изменение размера");
}

Resize::~Resize()
{
    delete ui;
}

void Resize::on_pushButton_clicked()
{
    try {
        newSize = stoi(ui->lineEdit->text().toStdString());
        value = stoi(ui->lineEdit_2->text().toStdString());
        sizeEntered = true;
        window()->close();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        sizeEntered = false;
    }
}

