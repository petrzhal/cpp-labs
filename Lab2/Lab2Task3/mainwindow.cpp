#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newexpression.h"
#include "expression.h"
#include "vector.cpp"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLayout>

QVector<Expression> tests;
QString newExpr;
double abcde[5]{};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_addExpr->setIcon(QPixmap("C:/QtLabs/Resources/add1.png"));
    ui->pushButton_changeExpr->setIcon(QPixmap("C:/QtLabs/Resources/edit.png"));
    GetTests();
    for (const auto& var : tests) {
        ui->listWidget->addItem(var.get_infix());
    }
    ui->pushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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

bool checked;

void MainWindow::on_pushButton_addExpr_clicked()
{
    NewExpression wind;
    wind.setModal(true);
    wind.exec();
    if (checked) {
        Expression expr(newExpr);
        expr.set_values(abcde[0], abcde[1], abcde[2], abcde[3], abcde[4]);
        tests.push_back(expr);
        ui->listWidget->addItem(expr.get_infix());
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton->setEnabled(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о выражении");
    window->setGeometry(QRect(430, 150, 800, 250));
    window->resize(650, 550);
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

    for (int i = 0; i < tests.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(tests[i].get_infix()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(tests[i].get_postfix()));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(tests[i].get_a())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(tests[i].get_b())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(tests[i].get_c())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(tests[i].get_d())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(tests[i].get_e())));
        tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(tests[i].evaluate())));
        tableWidget->resizeColumnsToContents();
        window->show();
    }
}


void MainWindow::on_pushButton_changeExpr_clicked()
{
    int row = ui->listWidget->currentRow();
    NewExpression wind(tests[row]);
    wind.setModal(true);
    wind.exec();
    if (checked) {
        Expression expr(newExpr);
        expr.set_values(abcde[0], abcde[1], abcde[2], abcde[3], abcde[4]);
        tests[row] = expr;
        ui->listWidget->clear();
        for (const auto& var : tests) {
            ui->listWidget->addItem(var.get_infix());
        }
    }
}

