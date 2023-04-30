#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table.h"
#include <QElapsedTimer>
#include <qcustomplot.h>

HashTable<int, int, 16> t16;
HashTable<int, int, 64> t64;
HashTable<int, int, 128> t128;
HashTable<int, int, 2048> t2048;

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

void MainWindow::ShowGraphic16() {
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);

    QVector<double> xData, yData;

    for (int i = 0; i < 500; ++i) {
        timer.start();
        t16[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
        qDebug() << "Size:" << i << ", Time:" << elapsed << "ms";
    }

    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);

    plot->xAxis->setLabel("Size");
    plot->yAxis->setLabel("Time, ms / 1000");
    plot->xAxis->setRange(0, 500);
    plot->yAxis->setRange(0, 0.004);
    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica", 9));
    plot->graph(0)->setName("Таблица на 16 элементов");

    plot->resize(400, 350);
    plot->move(QPoint(20, 20));

    plot->replot();
    plot->show();
}

void MainWindow::ShowGraphic64() {
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);

    QVector<double> xData, yData;

    for (int i = 0; i < 1000; ++i) {
        timer.start();
        t64[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
        qDebug() << "Size:" << i << ", Time:" << elapsed << "ms";
    }

    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);

    plot->xAxis->setLabel("Size");
    plot->yAxis->setLabel("Time, ms / 1000");
    plot->xAxis->setRange(0, 1000);
    plot->yAxis->setRange(0, 0.01);
    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica", 9));
    plot->graph(0)->setName("Таблица на 64 элемента");

    plot->resize(400, 350);
    plot->move(QPoint(440, 20));

    plot->replot();
    plot->show();
}

void MainWindow::ShowGraphic128() {
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);

    QVector<double> xData, yData;

    for (int i = 0; i < 2000; ++i) {
        timer.start();
        t128[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
        qDebug() << "Size:" << i << ", Time:" << elapsed << "ms";
    }

    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);

    plot->xAxis->setLabel("Size");
    plot->yAxis->setLabel("Time, ms / 1000");
    plot->xAxis->setRange(0, 2000);
    plot->yAxis->setRange(0, 0.02);
    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica", 9));
    plot->graph(0)->setName("Таблица на 128 элементов");

    plot->resize(400, 350);
    plot->move(QPoint(20, 390));

    plot->replot();
    plot->show();
}

void MainWindow::ShowGraphic2048() {
    QElapsedTimer timer;
    QCustomPlot* plot = new QCustomPlot(this);

    QVector<double> xData, yData;

    for (int i = 0; i < 10000; ++i) {
        timer.start();
        t2048[i];
        double elapsed = timer.nsecsElapsed() / 1000000.0;
        xData.append(i);
        yData.append(elapsed);
        qDebug() << "Size:" << i << ", Time:" << elapsed << "ms";
    }

    QCPGraph *graph = plot->addGraph();
    graph->setData(xData, yData);

    plot->xAxis->setLabel("Size");
    plot->yAxis->setLabel("Time, ms / 1000");
    plot->xAxis->setRange(0, 10000);
    plot->yAxis->setRange(0, 0.04);
    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica", 9));
    plot->graph(0)->setName("Таблица на 2048 элементов");

    plot->resize(400, 350);
    plot->move(QPoint(440, 390));

    plot->replot();
    plot->show();
}


void MainWindow::on_pushButton_graphics_clicked()
{
    ShowGraphic16();
    ShowGraphic64();
    ShowGraphic128();
    ShowGraphic2048();
}

