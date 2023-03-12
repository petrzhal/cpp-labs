#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "member.h"
#include "list.cpp"
#include "newplayer.h"
#include "weight.h"
#include "height.h"
#include "search.h"
#include <QFileDialog>
#include <fstream>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setEnabled(false);
    ui->lineEdit_filePath->setReadOnly(true);
    ui->lineEdit_nameFilter->setReadOnly(true);
    ui->lineEdit_teamFilter->setReadOnly(true);
    ui->lineEdit_countryFilter->setReadOnly(true);
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_add->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_showAll->setEnabled(false);
    ui->pushButton_showHeight->setEnabled(false);
    ui->pushButton_showWeight->setEnabled(false);
    ui->pushButton_showYoungest->setEnabled(false);
    ui->pushButton_findAge->setEnabled(false);
    ui->pushButton_findHeight->setEnabled(false);
    ui->pushButton_findWeight->setEnabled(false);
    ui->pushButton_findNum->setEnabled(false);
    ui->pushButton_delete->setIcon(QPixmap("C:/QtLabs/Resources/delete.png"));
    ui->pushButton_add->setIcon(QPixmap("C:/QtLabs/Resources/add.png"));
    ui->pushButton_edit->setIcon(QPixmap("C:/QtLabs/Resources/edit.png"));
    this->move(QPoint(500, 20));
}

MainWindow::~MainWindow()
{
    delete ui;
}

list players;
QVector<QVector<Member>> teams;
QVector<QVector<Member>> countries;
QString path;

bool IsTeamChecked(int ind) {
    for (int i = ind - 1; i >= 0; --i) {
        if (players[i].get_team() == players[ind].get_team())
            return true;
    }
    return false;
}

void UpdateTeams() {
    teams.clear();
    for (int i = 0; i < players.size(); ++i) {
        if (!IsTeamChecked(i)) {
            QVector<Member> team;
            for (int j = i; j < players.size(); ++j) {
                if (players[j].get_team() == players[i].get_team())
                    team.push_back(players[j]);
            }
            teams.push_back(team);
        }
    }
}

bool IsCountryChecked(int ind) {
    for (int i = ind - 1; i >= 0; --i) {
        if (players[i].get_country() == players[ind].get_country())
            return true;
    }
    return false;
}

void UpdateCountries() {
    countries.clear();
    for (int i = 0; i < players.size(); ++i) {
        if (!IsCountryChecked(i)) {
            QVector<Member> country;
            for (int j = i; j < players.size(); ++j) {
                if (players[j].get_country() == players[i].get_country())
                    country.push_back(players[j]);
            }
            countries.push_back(country);
        }
    }
}

void MainWindow::on_pushButton_chooseFile_clicked()
{
    ui->statusBar->showMessage("");
    players.clear();
    ui->listWidget->clear();
    path = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Docs (*.txt)"));

    std::fstream file;
    if (path.length()) {
        ui->lineEdit_filePath->setText(path);
        try {
            std::string stdPath = path.toStdString();
            std::string fileType;
            std::copy(stdPath.end() - 4, stdPath.end(), std::back_inserter(fileType));

            for (const auto& ch : stdPath)
                if (ch <= 0)
                    throw "Invalid file";
            if (fileType != ".txt")
                throw "Invalid file";
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

                players.push_back(member);
            }
            file.close();

            for (int i = 0; i < players.size(); ++i) {
                ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
            }
            UpdateTeams();
            ui->listWidget_teams->clear();
            for (const auto& team : teams) {
                ui->listWidget_teams->addItem(QString::fromStdString(team[0].get_team()));
            }
            ui->listWidget_countries->clear();
            UpdateCountries();
            for (const auto& country : countries) {
                ui->listWidget_countries->addItem(QString::fromStdString(country[0].get_country()));
            }
            ui->lineEdit_nameFilter->setReadOnly(false);
            ui->lineEdit_teamFilter->setReadOnly(false);
            ui->lineEdit_countryFilter->setReadOnly(false);
            ui->tabWidget->setEnabled(true);
            ui->pushButton_add->setEnabled(true);
            ui->pushButton_clear->setEnabled(true);
            ui->pushButton_showAll->setEnabled(true);
            ui->pushButton_showHeight->setEnabled(true);
            ui->pushButton_showWeight->setEnabled(true);
            ui->pushButton_showYoungest->setEnabled(true);
            ui->pushButton_findAge->setEnabled(true);
            ui->pushButton_findHeight->setEnabled(true);
            ui->pushButton_findWeight->setEnabled(true);
            ui->pushButton_findNum->setEnabled(true);
        } catch (...) {
            ui->lineEdit_filePath->setText("Файл не выбран");
            QMessageBox::critical(this, "Ошибка", "В выбранном файле нарушен формат записи данных");
            ui->lineEdit_nameFilter->setReadOnly(true);
            ui->lineEdit_teamFilter->setReadOnly(true);
            ui->lineEdit_countryFilter->setReadOnly(true);
            ui->tabWidget->setEnabled(false);
            ui->pushButton_edit->setEnabled(false);
            ui->pushButton_add->setEnabled(false);
            ui->pushButton_clear->setEnabled(false);
            ui->pushButton_delete->setEnabled(false);
            ui->pushButton_showAll->setEnabled(false);
            ui->pushButton_showHeight->setEnabled(false);
            ui->pushButton_showWeight->setEnabled(false);
            ui->pushButton_showYoungest->setEnabled(false);
            ui->pushButton_findAge->setEnabled(false);
            ui->pushButton_findHeight->setEnabled(false);
            ui->pushButton_findWeight->setEnabled(false);
            ui->pushButton_findNum->setEnabled(false);
        }
    }
    else {
        ui->lineEdit_filePath->setText("Файл не выбран");
        ui->lineEdit_nameFilter->setReadOnly(true);
        ui->lineEdit_teamFilter->setReadOnly(true);
        ui->lineEdit_countryFilter->setReadOnly(true);
        ui->tabWidget->setEnabled(false);
        ui->pushButton_edit->setEnabled(false);
        ui->pushButton_add->setEnabled(false);
        ui->pushButton_clear->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_showAll->setEnabled(false);
        ui->pushButton_showHeight->setEnabled(false);
        ui->pushButton_showWeight->setEnabled(false);
        ui->pushButton_showYoungest->setEnabled(false);
        ui->pushButton_findAge->setEnabled(false);
        ui->pushButton_findHeight->setEnabled(false);
        ui->pushButton_findWeight->setEnabled(false);
        ui->pushButton_findNum->setEnabled(false);
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->statusBar->showMessage("");
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
    ui->statusBar->showMessage("");
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
    ui->statusBar->showMessage("");
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
    UpdateTeams();
    ui->listWidget_teams->clear();
    for (const auto& team : teams) {
        ui->listWidget_teams->addItem(QString::fromStdString(team[0].get_team()));
    }
    ui->listWidget_countries->clear();
    UpdateCountries();
    for (const auto& country : countries) {
        ui->listWidget_countries->addItem(QString::fromStdString(country[0].get_country()));
    }
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

Member Player;

void MainWindow::on_pushButton_add_clicked()
{
    ui->statusBar->showMessage("");
    NewPlayer wind(FormCreationConfig::Add);
    wind.setModal(true);
    wind.exec();
    if (!Player.get_name().empty()) {
        players.push_back(Player);
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
        UpdateTeams();
        ui->listWidget_teams->clear();
        for (const auto& team : teams) {
            ui->listWidget_teams->addItem(QString::fromStdString(team[0].get_team()));
        }
        ui->listWidget_countries->clear();
        UpdateCountries();
        for (const auto& country : countries) {
            ui->listWidget_countries->addItem(QString::fromStdString(country[0].get_country()));
        }
    }
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

void MainWindow::on_pushButton_edit_clicked()
{
    ui->statusBar->showMessage("");
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
    UpdateTeams();
    ui->listWidget_teams->clear();
    for (const auto& team : teams) {
        ui->listWidget_teams->addItem(QString::fromStdString(team[0].get_team()));
    }
    ui->listWidget_countries->clear();
    UpdateCountries();
    for (const auto& country : countries) {
        ui->listWidget_countries->addItem(QString::fromStdString(country[0].get_country()));
    }
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


void MainWindow::on_listWidget_teams_itemDoubleClicked(QListWidgetItem *item)
{
    ui->statusBar->showMessage("");
    int ind = ui->listWidget_teams->currentRow();
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация об участниках из команды: " + QString::fromStdString(teams[ind][0].get_team()));
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
    for (int i = 0; i < teams[ind].size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(teams[ind][i].get_country())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(teams[ind][i].get_team())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(teams[ind][i].get_name())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(teams[ind][i].get_number())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(teams[ind][i].get_age())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(teams[ind][i].get_height())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(teams[ind][i].get_weight())));
    }
    tableWidget->resizeColumnsToContents();
    window->show();
    ui->statusBar->showMessage("");
}


void MainWindow::on_listWidget_countries_itemDoubleClicked(QListWidgetItem *item)
{
    ui->statusBar->showMessage("");
    int ind = ui->listWidget_countries->currentRow();
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация об участниках из страны: " + QString::fromStdString(countries[ind][0].get_country()));
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
    for (int i = 0; i < countries[ind].size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(countries[ind][i].get_country())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(countries[ind][i].get_team())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(countries[ind][i].get_name())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(countries[ind][i].get_number())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(countries[ind][i].get_age())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(countries[ind][i].get_height())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(countries[ind][i].get_weight())));
    }
    tableWidget->resizeColumnsToContents();
    window->show();
    ui->statusBar->showMessage("");
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->statusBar->showMessage("Щелкните дважды для просмотра информации");
    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_delete->setEnabled(true);
}


void MainWindow::on_listWidget_teams_itemClicked(QListWidgetItem *item)
{
    ui->statusBar->showMessage("Щелкните дважды для просмотра информации");
}


void MainWindow::on_listWidget_countries_itemClicked(QListWidgetItem *item)
{
    ui->statusBar->showMessage("Щелкните дважды для просмотра информации");
}

QPair<double, double> range;

void MainWindow::on_pushButton_showWeight_clicked()
{
    range = {-1, -1};
    ui->statusBar->showMessage("");
    Weight wind;
    wind.setModal(true);
    wind.exec();

    if (range.first >= 0 && range.second >= 0) {
        if (range.first > range.second) {
            QMessageBox::critical(this, "Ошибка", "Некорректная категория");
            return;
        }
        QVector<Member> inRangePlayers;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].get_weight() <= range.second && players[i].get_weight() >= range.first) {
                inRangePlayers.push_back(players[i]);
            }
        }
        if (inRangePlayers.size()) {
            QWidget *window = new QWidget();
            window->setWindowTitle("Информация об участниках из введенной весовой категории");
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
            for (int i = 0; i < inRangePlayers.size(); ++i) {
                tableWidget->insertRow(i);
                tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(inRangePlayers[i].get_country())));
                tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(inRangePlayers[i].get_team())));
                tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(inRangePlayers[i].get_name())));
                tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(inRangePlayers[i].get_number())));
                tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(inRangePlayers[i].get_age())));
                tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(inRangePlayers[i].get_height())));
                tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(inRangePlayers[i].get_weight())));
            }
            tableWidget->resizeColumnsToContents();
            window->show();
        }
        else {
            QMessageBox::information(this, "Пусто", "Участников из заданной весовой\nкатегории не найдено");
        }
    }
}

int neededHeight;

void MainWindow::on_pushButton_showHeight_clicked()
{
    ui->statusBar->showMessage("");
    neededHeight = 0;
    Height wind;
    wind.setModal(true);
    wind.exec();
    if (neededHeight) {
        QVector<Member> heightPlayers;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].get_height() >= neededHeight) {
                heightPlayers.push_back(players[i]);
            }
        }
        if (heightPlayers.size()) {
            QWidget *window = new QWidget();
            window->setWindowTitle("Информация об участниках с ростом не ниже введенного");
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
            for (int i = 0; i < heightPlayers.size(); ++i) {
                tableWidget->insertRow(i);
                tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(heightPlayers[i].get_country())));
                tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(heightPlayers[i].get_team())));
                tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(heightPlayers[i].get_name())));
                tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(heightPlayers[i].get_number())));
                tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(heightPlayers[i].get_age())));
                tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(heightPlayers[i].get_height())));
                tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(heightPlayers[i].get_weight())));
            }
            tableWidget->resizeColumnsToContents();
            window->show();
        }
        else {
              QMessageBox::information(this, "Пусто", "Участников с ростом не ниже введенного не найдено");
        }
    }
}

bool eqName(std::string str1, std::string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), tolower);
    transform(str2.begin(), str2.end(), str2.begin(), tolower);
    if (str1.find(str2, 0) != std::string::npos)
        return true;
    else
        return false;
}

void MainWindow::on_lineEdit_nameFilter_textChanged(const QString &arg1)
{
    ui->statusBar->showMessage("");
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->lineEdit_teamFilter->clear();
    ui->lineEdit_countryFilter->clear();
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); ++i) {
        if (eqName(players[i].get_name(), ui->lineEdit_nameFilter->text().toStdString())) {
            ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
        }
    }
}


void MainWindow::on_lineEdit_teamFilter_textChanged(const QString &arg1)
{
    ui->statusBar->showMessage("");
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->lineEdit_nameFilter->clear();
    ui->lineEdit_countryFilter->clear();
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); ++i) {
        if (eqName(players[i].get_team(), ui->lineEdit_teamFilter->text().toStdString())) {
            ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
        }
    }
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0 && !path.isEmpty()) {
        ui->lineEdit_nameFilter->setReadOnly(false);
        ui->lineEdit_teamFilter->setReadOnly(false);
        ui->lineEdit_countryFilter->setReadOnly(false);
        ui->pushButton_findAge->setEnabled(true);
        ui->pushButton_findHeight->setEnabled(true);
        ui->pushButton_findWeight->setEnabled(true);
        ui->pushButton_findNum->setEnabled(true);
    }
    else {
        ui->pushButton_findAge->setEnabled(false);
        ui->pushButton_findHeight->setEnabled(false);
        ui->pushButton_findWeight->setEnabled(false);
        ui->pushButton_findNum->setEnabled(false);
        ui->lineEdit_nameFilter->setReadOnly(true);
        ui->lineEdit_teamFilter->setReadOnly(true);
        ui->lineEdit_countryFilter->setReadOnly(true);
        ui->lineEdit_nameFilter->clear();
        ui->lineEdit_teamFilter->clear();
        ui->lineEdit_countryFilter->clear();
    }
}


void MainWindow::on_pushButton_showYoungest_clicked()
{
    int min = 0;
    int ind = 0;
    UpdateTeams();
    for (int i = 0; i < teams[0].size(); ++i) {
        min += teams[0][i].get_age();
    }
    min /= teams[0].size();
    for (int i = 1; i < teams.size(); ++i) {
        int age = 0;
        for (int j = 0; j < teams[i].size(); ++j) {
            age += teams[i][j].get_age();
        }
        age /= teams[i].size();
        if (age < min) {
            min = age;
            ind = i;
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о самой молодой команде");
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
    for (int i = 0; i < teams[ind].size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(teams[ind][i].get_country())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(teams[ind][i].get_team())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(teams[ind][i].get_name())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(teams[ind][i].get_number())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(teams[ind][i].get_age())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(teams[ind][i].get_height())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(teams[ind][i].get_weight())));
    }
    tableWidget->resizeColumnsToContents();
    window->show();
}


void MainWindow::on_lineEdit_countryFilter_textChanged(const QString &arg1)
{
    ui->statusBar->showMessage("");
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->lineEdit_nameFilter->clear();
    ui->lineEdit_teamFilter->clear();
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); ++i) {
        if (eqName(players[i].get_country(), ui->lineEdit_countryFilter->text().toStdString())) {
            ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
        }
    }
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->statusBar->showMessage("");
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); ++i) {
        ui->listWidget->addItem(QString::fromStdString(players[i].get_name()));
    }
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

int findHeight = 0;
int findAge = 0;
int findNumber = 0;
double findWeight = 0;
bool checked;

void MainWindow::on_pushButton_findHeight_clicked()
{
    checked = false;
    search wind(SearchOpenConfig::height);
    wind.setModal(true);
    wind.exec();
    if (!checked)
        return;
    if (findHeight) {
        QVector<Member> finded;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].get_height() == findHeight) {
                finded.push_back(players[i]);
            }
        }
        if (finded.size()) {
            ui->listWidget->clear();
            for (int i = 0; i < finded.size(); ++i) {
                ui->listWidget->addItem(QString::fromStdString(finded[i].get_name()));
            }
        }
        else {
            QMessageBox::information(this, "Пусто", "Участников с заданным ростом не найдено");
        }
    }
}

bool eqDouble(double ab1, double ab2) {
    double e = 0.01;
    if (ab2 >= ab1 - e && ab2 <= ab1 + e)
        return true;
    return false;
}

void MainWindow::on_pushButton_findWeight_clicked()
{
    checked = false;
    search wind(SearchOpenConfig::weight);
    wind.setModal(true);
    wind.exec();
    if (!checked)
        return;
    if (findWeight) {
        QVector<Member> finded;
        for (int i = 0; i < players.size(); ++i) {
            if (eqDouble(players[i].get_weight(), findWeight)) {
                finded.push_back(players[i]);
            }
        }
        if (finded.size()) {
            ui->listWidget->clear();
            for (int i = 0; i < finded.size(); ++i) {
                ui->listWidget->addItem(QString::fromStdString(finded[i].get_name()));
            }
        }
        else {
            QMessageBox::information(this, "Пусто", "Участников с заданным весом не найдено");
        }
    }
}


void MainWindow::on_pushButton_findNum_clicked()
{
    checked = false;
    search wind(SearchOpenConfig::number);
    wind.setModal(true);
    wind.exec();
    if (!checked)
        return;
    if (findNumber) {
        QVector<Member> finded;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].get_number() == findNumber) {
                finded.push_back(players[i]);
            }
        }
        if (finded.size()) {
            ui->listWidget->clear();
            for (int i = 0; i < finded.size(); ++i) {
                ui->listWidget->addItem(QString::fromStdString(finded[i].get_name()));
            }
        }
        else {
            QMessageBox::information(this, "Пусто", "Участников с заданным номером не найдено");
        }
    }
}


void MainWindow::on_pushButton_findAge_clicked()
{
    checked = false;
    search wind(SearchOpenConfig::age);
    wind.setModal(true);
    wind.exec();
    if (!checked)
        return;
    if (findAge) {
        QVector<Member> finded;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].get_age() == findAge) {
                finded.push_back(players[i]);
            }
        }
        if (finded.size()) {
            ui->listWidget->clear();
            for (int i = 0; i < finded.size(); ++i) {
                ui->listWidget->addItem(QString::fromStdString(finded[i].get_name()));
            }
        }
        else {
            QMessageBox::information(this, "Пусто", "Участников с заданным возрастом не найдено");
        }
    }
}
