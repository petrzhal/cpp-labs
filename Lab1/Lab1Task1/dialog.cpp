#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::Dialog(const QString& str) : ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText(str);
}

Dialog::~Dialog()
{
    delete ui;
}
