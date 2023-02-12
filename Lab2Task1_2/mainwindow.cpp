#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "member.h"
#include "list.cpp"
#include "newplayer.h"
//#include "ui_newplayer.h"
#include <QFileDialog>
#include <fstream>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

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

list<Member> players;
QString path;

void MainWindow::on_pushButton_chooseFile_clicked()
{
    players.clear();
    ui->listWidget->clear();
    path = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Docs (*.txt)"));

    std::fstream file;
    if (path.length()) {
        ui->lineEdit_filePath->setText(path);
        try {
            file.open(path.toStdString(), std::ios::in);
            if (!file.is_open())
                throw "Invalid file";
            for (int i = 0; file.peek() != EOF; ++i) {
                Member member;
                std::string str;
                std::getline(file, str);
                member.set_country(str);

                std::getline(file, str);
                member.set_team(str);

                std::getline(file, str);
                member.set_name(str);

                int n;
                file >> n;
                member.set_number(n);

                file >> n;
                member.set_age(n);

                file >> n;
                member.set_height(n);

                double w;
                file >> w;
                member.set_weight(w);

                std::getline(file, str);

                players.addEnd(member);
            }
            file.close();

            for (int i = 0; i < players.size(); ++i) {
                ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
            }
        } catch (...) {
            QMessageBox::critical(this, "Ошибка", "Выбранный файл не поддерживается");
            ui->lineEdit_filePath->setText("Файл не выбран");
            ui->lineEdit_filePath->clear();
        }
    }
    else {
        ui->lineEdit_filePath->setText("Файл не выбран");
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int ind = 0;
    for (int i = 0; i < players.size(); ++i) {
        if (ui->listWidget->currentItem()->text().toStdString() == players[i].get_name()) {
            ind = i;
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация об участниках");
    window->setGeometry(QRect(400, 350, 800, 250));
    window->resize(750, 10);
    QTableWidget *tableWidget = new QTableWidget();
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(7);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("Страна");
            headers1.append("Команда");
            headers1.append("ФИО");
            headers1.append("Игровой номер");
            headers1.append("Возраст");
            headers1.append("Рост");
            headers1.append("Вес");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    tableWidget->insertRow(0);
    tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(players[ind].get_country())));
    tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(players[ind].get_team())));
    tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(players[ind].get_name())));
    tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(players[ind].get_number())));
    tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(players[ind].get_age())));
    tableWidget->setItem(0, 5, new QTableWidgetItem(QString::number(players[ind].get_height())));
    tableWidget->setItem(0, 6, new QTableWidgetItem(QString::number(players[ind].get_weight())));
    tableWidget->resizeColumnsToContents();
    window->show();
}


void MainWindow::on_pushButton_showAll_clicked()
{
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация об участнике");
    window->setGeometry(QRect(400, 200, 800, 250));
    window->resize(750, 500);
    QTableWidget *tableWidget = new QTableWidget();
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(7);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("Страна");
            headers1.append("Команда");
            headers1.append("ФИО");
            headers1.append("Игровой номер");
            headers1.append("Возраст");
            headers1.append("Рост");
            headers1.append("Вес");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < players.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(players[i].get_country())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(players[i].get_team())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(players[i].get_name())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(players[i].get_number())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(players[i].get_age())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(players[i].get_height())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(players[i].get_weight())));
    }
    tableWidget->resizeColumnsToContents();
    window->show();
}


void MainWindow::on_pushButton_delete_clicked()
{
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].get_name() == ui->listWidget->currentItem()->text().toStdString()) {
            players.erase(i);
        }
    }
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); ++i) {
        ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
    }
    std::fstream file;
    file.open(path.toStdString(), std::ios::out | std::ios::trunc);
    for (int i = 0; i < players.size(); ++i) {
        file << players[i].get_country() << "\n";
        file << players[i].get_team() << "\n";
        file << players[i].get_name() << "\n";
        file << players[i].get_number() << " ";
        file << players[i].get_age() << " ";
        file << players[i].get_height() << " ";
        file << players[i].get_weight();
        if (i != players.size() - 1)
            file << "\n";
    }
    file.close();
}

Member Player;

void MainWindow::on_pushButton_add_clicked()
{
    NewPlayer wind(FormCreationConfig::Add);
    wind.setModal(true);
    wind.exec();
    players.addEnd(Player);
    std::fstream file;
    file.open(path.toStdString(), std::ios::out | std::ios::app);
    file << "\n" << Player.get_country() << "\n";
    file << Player.get_team() << "\n";
    file << Player.get_name() << "\n";
    file << Player.get_number() << " ";
    file << Player.get_age() << " ";
    file << Player.get_height() << " ";
    file << Player.get_weight();
    file.close();
    ui->listWidget->addItem(QString::fromStdString(players.end()->data.get_name()));
}

void MainWindow::on_pushButton_edit_clicked()
{
    int ind = 0;
    for (int i = 0; i < players.size(); ++i) {
        if (ui->listWidget->currentItem()->text().toStdString() == players[i].get_name()) {
            Player = players[i];
            ind = i;
            break;
        }
    }
    NewPlayer wind(FormCreationConfig::Change);
    wind.setModal(true);
    wind.exec();
    players[ind] = Player;
    std::fstream file;
    file.open(path.toStdString(), std::ios::out | std::ios::trunc);
    for (int i = 0; i < players.size(); ++i) {
        file << players[i].get_country() << "\n";
        file << players[i].get_team() << "\n";
        file << players[i].get_name() << "\n";
        file << players[i].get_number() << " ";
        file << players[i].get_age() << " ";
        file << players[i].get_height() << " ";
        file << players[i].get_weight();
        if (i != players.size() - 1)
            file << "\n";
    }
    file.close();
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); ++i) {
        ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
    }
}

