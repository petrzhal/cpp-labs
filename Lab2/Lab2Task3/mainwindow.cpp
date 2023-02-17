#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "expression.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Expression expr(ui->lineEdit->text());
    ui->textBrowser->append(expr.PostfixForm());
    ui->textBrowser->append(QString::number(expr.Evaluate(ui->lineEdit_a->text().toDouble(), ui->lineEdit_b->text().toDouble(),  ui->lineEdit_c->text().toDouble(),  ui->lineEdit_d->text().toDouble(),  ui->lineEdit_e->text().toDouble())));
}

