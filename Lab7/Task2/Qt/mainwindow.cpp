#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include <QMessageBox>

map<int, QString> tree;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Show()
{
    ui->treeWidget->clear();
    ui->lineEdit->clear();
    QString line;
    for (const auto& el : tree) {
        line.append(QString::number(el.first) + " ");
    }
    ui->lineEdit->setText(line);
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(rootItem);
    addNode(tree.get_root(), rootItem);
}

void MainWindow::on_pushButton_deleteKey_clicked()
{
    try {
        tree.erase(stoi(ui->lineEdit_key->text().toStdString()));
        Show();
        ui->lineEdit_key->clear();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ключ");
    }
}

void MainWindow::on_pushButton_insert_clicked()
{
    try {
        int val = stoi(ui->lineEdit_key->text().toStdString());
        tree.insert(val, QString::number(val));
        Show();
        ui->lineEdit_key->clear();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ключ");
    }
}

