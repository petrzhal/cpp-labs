#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solve.h"

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

Solve slv;

void MainWindow::on_pushButton_create_clicked()
{
    slv.CreateQueue();
    ui->textBrowser->setText(slv.ToString());
}

void MainWindow::on_pushButton_clear_clicked()
{
    slv.Clear();
    ui->textBrowser->setText(slv.ToString());
}

void MainWindow::on_pushButton_delete_clicked()
{
    slv.DeleteMinMax();
    ui->textBrowser->setText(slv.ToString());
}

