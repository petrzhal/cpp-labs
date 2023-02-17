#include "height.h"
#include "ui_height.h"
#include <QMessageBox>

extern int neededHeight;

Height::Height(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Height)
{
    ui->setupUi(this);
}

Height::~Height()
{
    delete ui;
}

void Height::on_pushButton_clicked()
{
    try {
        neededHeight = ui->lineEdit->text().toInt();
        this->setWindowTitle("Ввод роста");
        window()->close();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный рост");
        ui->lineEdit->clear();
    }
}

