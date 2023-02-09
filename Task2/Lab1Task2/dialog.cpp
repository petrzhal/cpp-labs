#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}



Dialog::Dialog(const QString& instruction) : ui(new Ui::Dialog) {
    ui->setupUi(this);
    if (instruction == "name") {
        ui->label->setText("Введите искомое ФИО");
    }
    else if (instruction == "group") {
        ui->label->setText("Введите искомый номер группы");
    }
    else if (instruction == "form") {
        ui->label->setText("Введите искомую форму обучения");
    }
    instr = instruction;
}

Dialog::~Dialog()
{
    delete ui;
}

