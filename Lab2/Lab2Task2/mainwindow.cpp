#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include "stack.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Проверка скобок");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString path;

void MainWindow::on_open_triggered()
{
    path = QFileDialog::getOpenFileName(this, tr("Open File"), "F:/", tr("Text Docs (*.txt)"));
    if (!path.length())
        return;
    QFile qfile(path);
    qfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream file(&qfile);
    ui->textEdit->setText(file.readAll());
    qfile.close();
}


void MainWindow::on_save_triggered()
{
    QFile qfile(path);
    if (!path.length())
        return;
    qfile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream file(&qfile);
    file << ui->textEdit->toPlainText();
    qfile.close();
}


void MainWindow::on_save_as_triggered()
{
    path = QFileDialog::getSaveFileName(this, tr("Open File"), "F:/", tr("Text Docs (*.txt)"));
    if (!path.length())
        return;
    QFile qfile(path);
    qfile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream file(&qfile);
    file << ui->textEdit->toPlainText();
    qfile.close();
}

bool cmp(int a, int b) {
    if (a && !b)
        return true;
    else if (!a && b)
        return false;
    else if (a < b)
        return true;
    else
        return false;
}

QPair<int, int> Bracketscorrect(const QString& str) {
    stack<int> stackFigure;
    stack<int> stackSquare;
    stack<int> stackRound;
    char figL = '{', figR = '}';
    char sqrL = '[', sqrR = ']';
    char rndL = '(', rndR = ')';

    int indFigure;
    int indSquare;
    int indRound;

    int kal[3]{};
    bool err1 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == figL)
            stackFigure.push(i);
        else if (str[i] == figR) {
            if (stackFigure.size() > 0)
                stackFigure.pop();
            else {
                indFigure =  i + 1;
                kal[0] = indFigure;
                err1 = true;
                break;
            }
        }
    }
    if (!err1 && stackFigure.size() > 0) {
        while (stackFigure.size() != 1) {
            stackFigure.pop();
        }
        indFigure = stackFigure.top() + 1;
    }
    else if (!err1) {
        indFigure = 0;
    }

    bool err2 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == sqrL)
            stackSquare.push(i);
        else if (str[i] == sqrR) {
            if (stackSquare.size() > 0)
                stackSquare.pop();
            else {
                indSquare =  i + 1;
                kal[1] = indSquare;
                err2 = true;
                break;
            }
        }
    }
    if (!err2 && stackSquare.size() > 0) {
        while (stackSquare.size() != 1) {
            stackSquare.pop();
        }
        indSquare = stackSquare.top() + 1;
    }
    else if (!err2) {
        indSquare = 0;
    }
    bool err3 = false;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == rndL)
            stackRound.push(i);
        else if (str[i] == rndR) {
            if (stackRound.size() > 0)
                stackRound.pop();
            else {
                indRound =  i + 1;
                kal[2] = indRound;
                err3 = true;
                break;
            }
        }
    }
    if (!err3 && stackRound.size() > 0) {
        while (stackRound.size() != 1) {
            stackRound.pop();
        }
        indRound = stackRound.top() + 1;
    }
    else if (!err3) {
        indRound = 0;
    }
    int res;
    if (kal[0] || kal[1] || kal[2]) {
        res = std::min(std::min(kal[0], kal[1], cmp), kal[2], cmp);
    }
    else {
        if (indFigure && indRound && indSquare) {
            res = 0;
        }
        else {
            res = std::min(std::min(indFigure, indRound, cmp), indSquare, cmp);
        }
    }
    int row = 1;
    int col = 0;
    QPair<int, int> pos;
    for (int i = 0; i < res; ++i) {
        if (str[i] == '\n') {
            row++;
            col = 0;
        }
        else col++;
        pos.first = row;
        pos.second = col;
    }
    return pos;
}


void MainWindow::on_textEdit_textChanged()
{
    if (Bracketscorrect(ui->textEdit->toPlainText()).first == 0 && Bracketscorrect(ui->textEdit->toPlainText()).second == 0) {
        ui->statusbar->showMessage("Проблем не найдено");
    }
    else {
        ui->statusbar->showMessage("Ошибка: строка: " + QString::number(Bracketscorrect(ui->textEdit->toPlainText()).first) + ", столбец: " + QString::number(Bracketscorrect(ui->textEdit->toPlainText()).second));
    }
}


