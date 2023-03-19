#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newelement.h"
#include "vector.cpp"
#include "pair.cpp"

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

QString toString(const vector<int>& vec) {
    QString kal;
    for (int i = 0; i < vec.size(); ++i) {
        kal += QString::number(vec[i]);
        kal.push_back(' ');
    }
    return kal;
}

QString toString(const vector<pair<int, double>>& vec) {
    QString kal;

    for (int i = 0; i < vec.size(); ++i) {
        kal += QString::number(vec[i].first) + " " + QString::number(vec[i].second);
        kal.push_back(' ');
    }
    return kal;
}

vector<pair<vector<int>, vector<pair<int, double>>>> matrix;
vector<int> firstNew;
vector<pair<int, double>> secondNew;
bool isNewAdded = false;

void MainWindow::on_pushButton_add_clicked()
{
    NewElement wind;
    wind.setModal(true);
    wind.exec();
        ui->textBrowser->clear();
        ui->textBrowser_2->clear();
        matrix.push_back(make_pair(firstNew, secondNew));
        for (int i = 0; i < matrix.size(); ++i) {
            ui->textBrowser->append(toString(matrix[i].first));
            ui->textBrowser_2->append(toString(matrix[i].second));
        }
}

