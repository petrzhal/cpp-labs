#include "birthdayinput.h"
#include "ui_birthdayinput.h"


BirthdayInput::BirthdayInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BirthdayInput)
{
    ui->setupUi(this);

    connect(this, SIGNAL(k()), this, SLOT(MainWindow::kostyl()));
}

BirthdayInput::~BirthdayInput()
{
    delete ui;
}



