#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solve.h"
#include <QMessageBox>

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

void MainWindow::Show() {
    ui->listWidget->clear();
    auto stacks = slv.Stacks();
    for (const auto &var : stacks) {
        if (var.size())
            ui->listWidget->addItem(var);
        else
            ui->listWidget->addItem("null");
    }
}

void MainWindow::on_pushButton_create_clicked()
{
    slv.clear();
    slv.CreateRandom(-10, 10);
    Show();
}


void MainWindow::on_pushButton_removeNegative_clicked()
{
    slv.RemoveNegative();
    Show();
}


void MainWindow::on_pushButton_random_clicked()
{
    slv.clear();
    slv.CreateRandom(-50, 50);
    Show();
}


void MainWindow::on_pushButton_remove_clicked()
{
    try {
        int key = stoi(ui->lineEdit_remove->text().toStdString());
        slv.erase(key);
        Show();
    } catch(...) {
        ui->lineEdit_remove->clear();
        QMessageBox::critical(this, "Ошибка", "Некорректный ключ");
    }
}

void MainWindow::on_pushButton_insert_clicked()
{
    try {
        int key = stoi(ui->lineEdit_insert->text().toStdString());
        slv.insert(key, 0);
        Show();
    } catch(...) {
        ui->lineEdit_insert->clear();
        QMessageBox::critical(this, "Ошибка", "Некорректный ключ");
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    slv.clear();
    Show();
}

