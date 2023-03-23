#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "C:/QtLabs/Lab3/Lib/Vector/vector.h"
#include "resize.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Работа с вектором целых чисел типа int");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString toString(const vector<int>& vec) {
    QString kal;
    for (int i = 0; i < vec.size(); ++i) {
        kal += QString::number(vec[i]);
        kal.push_back(' ');
    }
    return kal;
}

vector<int> vec;

void MainWindow::on_pushButton_add_clicked()
{
    try {
        vec.emplace_back(stoi(ui->lineEdit->text().toStdString()));
        ui->lineEdit->clear();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
    }
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}


void MainWindow::on_pushButton_insert_clicked()
{
    try {
        int ind = stoi(ui->lineEdit_index->text().toStdString());
        if (ind < 0 || ind >= vec.size()) {
            throw "Incorrect index";
        }
        auto it = vec.begin();
        for (int i = 0; i < ind; ++i) {
            it++;
        }
        vec.insert(it, stoi(ui->lineEdit_value->text().toStdString()));
        ui->lineEdit_index->clear();
        ui->lineEdit_value->clear();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        ui->lineEdit_index->clear();
        ui->lineEdit_value->clear();
    }
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}


void MainWindow::on_pushButton_capacity_clicked()
{
    ui->textBrowser->setText("Capacity: " + QString::number(vec.capacity()));
}


void MainWindow::on_pushButton_show_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}


void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->setText("Size: " + QString::number(vec.size()));
}

int newSize;
bool sizeEntered;
int value;

void MainWindow::on_pushButton_changeSize_clicked()
{
    sizeEntered = false;
    Resize wind;
    wind.setModal(true);
    wind.exec();
    if (sizeEntered) {
        vec.resize(newSize, value);
        ui->textBrowser->clear();
        ui->textBrowser->append(toString(vec));
    }
}


void MainWindow::on_pushButton_deleteInd_clicked()
{
    try {
        int ind = stoi(ui->lineEdit_deleteInd->text().toStdString());
        if (ind < 0 || ind >= vec.size()) {
            throw "Incorrect index";
        }
        auto it = vec.begin();
        for (int i = 0; i < ind; ++i) {
            it++;
        }
        vec.erase(it);
        ui->lineEdit_deleteInd->clear();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        ui->lineEdit_deleteInd->clear();
    }
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}


void MainWindow::on_pushButton_deleteFew_clicked()
{
    try {
        int begin = stoi(ui->lineEdit_deleteBegin->text().toStdString());
        int end = stoi(ui->lineEdit_deleteEnd->text().toStdString());
        if (begin >= end) {
            throw "Incorrect index";
        }
        if (begin < 0 || begin > vec.size()) {
            throw "Incorrect index";
        }
        if (end < 0 || end > vec.size()) {
            throw "Incorrect index";
        }
        auto begIt = vec.begin();
        auto endIt = vec.begin();
        for (int i = 0; i < begin; ++i) {
            begIt++;
        }
        for (int i = 0; i < end; ++i) {
            endIt++;
        }
        vec.erase(begIt, endIt);
        ui->lineEdit_deleteBegin->clear();
        ui->lineEdit_deleteEnd->clear();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        ui->lineEdit_deleteBegin->clear();
        ui->lineEdit_deleteEnd->clear();
    }
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}


void MainWindow::on_pushButton_popback_clicked()
{
    vec.pop_back();
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}


void MainWindow::on_pushButton_clear_clicked()
{
    vec.clear();
    ui->textBrowser->clear();
    ui->textBrowser->append(toString(vec));
}

