#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parser.h"
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setStyleSheet("color: white;");
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
    auto res = prs.get_variables();
    ui->textBrowser->append("Variables: " + QString::number(res.size()));
    for (auto &type: res) {
        ui->textBrowser->append(QString::fromStdString(type.first) + "    (" + QString::number(type.second.first) + ", " + QString::number(type.second.second) + ")");
    }

    auto res3 = prs.get_arrays();
    ui->textBrowser->append("\nArrays: " + QString::number(res3.size()));
    for (auto &type: res3) {
        ui->textBrowser->append(QString::fromStdString(type));
    }

    ui->textBrowser->append("\nClasses: " + QString::number(prs.get_classes().size()));
    res3 = prs.get_classes();
    for (auto &type: res3) {
        ui->textBrowser->append(QString::fromStdString(type));
    }

    res3 = prs.get_structs();
    ui->textBrowser->append("\nStructs: " + QString::number(prs.get_structs().size()));
    for (auto &type: res3) {
        ui->textBrowser->append(QString::fromStdString(type));
    }

    ui->textBrowser->append("\nFunction prototypes: " + QString::number(prs.get_prototypes().size()));
    auto res2 = prs.get_prototypes();
    for (auto &type : res2) {
        ui->textBrowser->append(QString::fromStdString(type.first.first));
    }

    auto pr = prs.overloadedFuncCount();
    ui->textBrowser->append("\nOverloaded functions: " + QString::number(pr.second));
    for (const auto& p : pr.first) {
        ui->textBrowser->append(QString::fromStdString(p.first) + "    (" + QString::number(p.second.first) + ", " + QString::number(p.second.first) + ")");
    }

    auto er = prs.logicErrors();
    if (er.empty())
        ui->textBrowser->append("\nLogic errors: 0");
    else
        ui->textBrowser->append("\nLogic errors: ");
    for (auto &error: er) {
        ui->textBrowser->append(QString::fromStdString(error.first) + "    (" + QString::number(error.second.first) + ", " + QString::number(error.second.second) + ")");
    }

    auto ch = prs.variablesChanges();
    ui->textBrowser->append("\nСhanging variables: ");
    for (auto &change: ch) {
        ui->textBrowser->append(QString::fromStdString(change.first) + "    (" + QString::number(change.second.first) + ", " + QString::number(change.second.second) + ")");
    }

    ui->textBrowser->append("\nBranches: ");
    prs.findBranches();
    auto r = prs.get_branchesCount();
    for (size_t i = 0; i < lines.size(); ++i) {
        if (r[i])
            ui->textBrowser->append(QString::fromStdString(lines[i].substr(0, lines[i].size() - 1)) + "    Depth: " + QString::number(static_cast<int>(std::log(r[i] * 2) / std::log(2))));
    }
}


void MainWindow::on_action_triggered()
{
    ui->textBrowser->clear();
    QString path = QFileDialog::getOpenFileName(this, "", "C:/QtLabs/Lab4_", "*.c *.cpp *.h *.hpp");
    QFile qFile(path);
    qFile.open(QIODevice::ReadOnly);
    QTextStream file(&qFile);
    QString buf = file.readAll();
    ui->textEdit->setPlainText(buf);
    qFile.close();
}

