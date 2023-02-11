#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_filePath->setReadOnly(true);

}
MainWindow::~MainWindow()
{
    delete ui;
}

QString path;

void MainWindow::on_pushButton_chooseFile_clicked()
{
    path = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Docs (*.txt)"));

    std::fstream file;
    if (path.length()) {
        ui->lineEdit_filePath->setText(path);
        try {
            file.open(path.toStdString(), std::ios::in);

            file.close();
        } catch (...) {

        }
    }
    else {
        ui->lineEdit_filePath->setText("Файл не выбран");
    }
}

