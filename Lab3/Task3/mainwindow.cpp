#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "C:/QtLabs/Lab3/Lib/Vector/vector.h"
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

vector<int> sequence;

QString toString(const vector<int>& vec) {
    QString kal;
    for (int i = 0; i < vec.size(); ++i) {
        kal += QString::number(vec[i]);
        kal.push_back(' ');
    }
    return kal;
}

void MainWindow::on_pushButton_add_clicked()
{
    ui->textBrowser->clear();
    try {
        sequence.push_back(stoi(ui->lineEdit->text().toStdString()));
        ui->lineEdit->clear();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
    }
    ui->textBrowser->append(toString(sequence));
}


void MainWindow::on_pushButton_clicked()
{
    vector<int> res;
    for (int i = 0; i < sequence.size(); i += 3) {
        vector<int> a;
        for (int j = i ; j < i + 3 && j < sequence.size(); ++j) {
            a.push_back(sequence[j]);
        }
        if (a.size() == 3) {
            int mid = (a[0] + a[1] + a[2]) - std::max(a[0], std::max(a[1], a[2])) - std::min(a[0], (a[1], a[2]));
            res.push_back(mid);
        }
        else if (a.size() == 2) {
            int average = (a[0] + a[1]) / 2;
            res.push_back(average);
        }
        else {
            QMessageBox::critical(this, "Ошибка", "Неверное количество чисел");
            return;
        }
    }
    ui->textBrowser->append("Вектор из медиан идущих подряд троек:");
    ui->textBrowser->append(toString(res));
}

