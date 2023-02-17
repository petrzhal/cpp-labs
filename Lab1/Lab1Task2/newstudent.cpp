#include "newstudent.h"
#include "ui_newstudent.h"

NewStudent::NewStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewStudent)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление");
}

NewStudent::NewStudent(const Student& st) :
    ui(new Ui::NewStudent)
{
    ui->setupUi(this);
    this->setWindowTitle("Изменение");
    ui->lineEdit_name->setText(QString::fromStdString(st.get_name()));
    ui->lineEdit_speciality->setText(QString::fromStdString(st.get_speciality()));
    ui->lineEdit_form->setText(st.get_form());
    ui->lineEdit_group->setText(st.get_group());
    ui->lineEdit_mark1->setText(QString::number(st.get_mark1()));
    ui->lineEdit_mark2->setText(QString::number(st.get_mark2()));
    ui->lineEdit_mark3->setText(QString::number(st.get_mark3()));
}

NewStudent::~NewStudent()
{
    delete ui;
}
