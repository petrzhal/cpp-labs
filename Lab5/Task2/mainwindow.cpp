#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deque.h"

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

deque<int> a;

QString toLine() {
    QString line;
//    for (size_t i = 0; i < a.size(); ++i) {
//        line += QString::number(a[i]) + " ";
//    }
    for (const auto& el : a) {
        line += QString::number(el) + " ";
    }
    return line;
}

void MainWindow::on_pushButton_push_front_clicked()
{
    a.push_front(rand() % 100);
    ui->textBrowser->setText(toLine());
}


void MainWindow::on_pushButton_push_back_clicked()
{
    a.push_back(rand() % 100);
    ui->textBrowser->setText(toLine());
}


void MainWindow::on_pushButton_pop_front_clicked()
{
    a.pop_front();
    ui->textBrowser->setText(toLine());
}


void MainWindow::on_pushButton_pop_back_clicked()
{
    a.pop_back();
    ui->textBrowser->setText(toLine());
}


void MainWindow::on_pushButton_clear_clicked()
{
    a.clear();
    ui->textBrowser->setText(toLine());
}


void MainWindow::on_pushButton_size_clicked()
{
    ui->textBrowser->setText("size = " + QString::number(a.size()));
}

void MainWindow::on_pushButton_capacity_clicked()
{
    ui->textBrowser->setText("capacity = " + QString::number(a.capacity()));
}


void MainWindow::on_pushButton_empty_clicked()
{
    ui->textBrowser->setText(a.empty() ? "True" : "False");
}

