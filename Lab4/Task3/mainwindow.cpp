#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parser.hpp"

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

void MainWindow::on_pushButton_parse_clicked()
{
    ui->textBrowser->clear();
    std::vector<std::string> lines;
    QString text = ui->textEdit->toPlainText();
    QString line;
    for (int i = 0; i < text.size(); ++i) {
        line.push_back(text[i]);
        if (text[i] == '\n') {
            lines.push_back(line.toStdString());
            line.clear();
        }
    }
    parser prs(lines);
    auto types = prs.get_types();
        ui->textBrowser->append("Types:");
        for (const auto &type: types) {
            ui->textBrowser->append(QString::fromStdString(type));
        }
        ui->textBrowser->append("\nVariables:");
        auto res = prs.get_variables();
        for (auto &type: res) {
            ui->textBrowser->append(QString::fromStdString(type.first) + " (" + QString::number(type.second.first) + ", " + QString::number(type.second.second) + ")");
        }
        ui->textBrowser->append("\nArrays:");
        auto res3 = prs.get_arrays();
        for (auto &type: res3) {
            ui->textBrowser->append(QString::fromStdString(type));
        }
        ui->textBrowser->append("\nFunction prototypes:");
        auto res2 = prs.get_prototypes();
        for (auto &type : res2) {
            ui->textBrowser->append(QString::fromStdString(type.first.first));
        }
        auto pr = prs.overloadedFuncCount();
        ui->textBrowser->append("\nOverloaded functions: " + QString::number(pr.second));
        for (const auto& p : pr.first) {
            ui->textBrowser->append("(" + QString::number(p.first) + ", " + QString::number(p.second) + ")");
        }
}

