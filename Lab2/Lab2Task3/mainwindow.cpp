#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "expression.h"
#include "vector.cpp"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

QVector<Expression> tests;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetTests();
    for (const auto& var : tests) {
        ui->listWidget->addItem(var.get_infix());
        //ui->textBrowser->append(QString::number(var.evaluate()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Expression expr(ui->lineEdit->text());
    //ui->textBrowser->append(expr.PostfixForm());
    ui->textBrowser->append(QString::number(expr.evaluate()));
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int ind = 0;
    for (int i = 0; i < tests.size(); ++i) {
        if (ui->listWidget->currentItem()->text() == tests[i].get_infix()) {
            ind = i;
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о выражении");
    window->setGeometry(QRect(450, 350, 800, 250));
    window->resize(650, 10);
    QTableWidget *tableWidget = new QTableWidget();
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(8);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("Инфиксная форма");
            headers1.append("Постфиксная форма");
            headers1.append("a");
            headers1.append("b");
            headers1.append("c");
            headers1.append("d");
            headers1.append("e");
            headers1.append("Результат");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    tableWidget->insertRow(0);
    tableWidget->setItem(0, 0, new QTableWidgetItem(tests[ind].get_infix()));
    tableWidget->setItem(0, 1, new QTableWidgetItem(tests[ind].get_postfix()));
    tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(tests[ind].get_a())));
    tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(tests[ind].get_b())));
    tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(tests[ind].get_c())));
    tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(tests[ind].get_d())));
    tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(tests[ind].get_e())));
    tableWidget->setItem(0, 7, new QTableWidgetItem(QString::number(tests[ind].evaluate())));
    tableWidget->resizeColumnsToContents();
    window->show();
}

