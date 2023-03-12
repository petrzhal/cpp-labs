#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "abiturient.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "search.h"
#include "ui_search.h"
#include "list.cpp"
#include "mergesort.cpp"
#include <QFileDialog>
#include <fstream>
#include <algorithm>
#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    window()->setWindowTitle("Task1");
    ui->pushButton_add->setEnabled(false);
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_findAverage->setEnabled(false);
    ui->pushButton_findMath->setEnabled(false);
    ui->pushButton_findName->setEnabled(false);
    ui->pushButton_findRus->setEnabled(false);
    ui->pushButton_findPhys->setEnabled(false);
    ui->pushButton_showUpperAverage->setEnabled(false);
    ui->pushButton_sort->setEnabled(false);
    ui->pushButton_show->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

list abList;
QString fileName;

void MainWindow::on_pushButton_chooseFile_clicked()
{
    ui->listWidget->clear();
    abList.clear();

    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Docs (*.txt)"));

    if (fileName.length()) {
        ui->lineEdit->setText(fileName);
        try {
            std::string path = fileName.toStdString();
            std::string fileType;
            std::copy(path.end() - 4, path.end(), std::back_inserter(fileType));

            for (const auto& ch : path)
                if (ch < 0)
                    throw "Invalid file";
            if (fileType != ".txt")
                throw "Invalid file";

            std::fstream file;
            file.open(fileName.toStdString(), std::ios::in);
            for (int i = 0; file.peek() != EOF; ++i) {
                abiturient ab;

                std::string buf;
                std::getline(file, buf);

                ab.set_name(buf);

                int rus, math, phys;
                file >> rus >> math >> phys;

                ab.set_marks(rus, math ,phys);

                std::getline(file, buf);

                abList.addEnd(ab);
            }
            file.close();

            for (int i = 0; i < abList.size(); ++i) {
                ui->listWidget->addItem(abList[i].get_name());
            }
            ui->pushButton_add->setEnabled(true);
            ui->pushButton_findAverage->setEnabled(true);
            ui->pushButton_findMath->setEnabled(true);
            ui->pushButton_findName->setEnabled(true);
            ui->pushButton_findRus->setEnabled(true);
            ui->pushButton_clear->setEnabled(true);
            ui->pushButton_findPhys->setEnabled(true);
            ui->pushButton_showUpperAverage->setEnabled(true);
            ui->pushButton_sort->setEnabled(true);
            ui->pushButton_show->setEnabled(true);
        } catch (...) {
            ui->lineEdit->setText("Файл не выбран");
            ui->pushButton_add->setEnabled(false);
            ui->pushButton_change->setEnabled(false);
            ui->pushButton_clear->setEnabled(false);
            ui->pushButton_delete->setEnabled(false);
            ui->pushButton_findAverage->setEnabled(false);
            ui->pushButton_findMath->setEnabled(false);
            ui->pushButton_findName->setEnabled(false);
            ui->pushButton_findRus->setEnabled(false);
            ui->pushButton_findPhys->setEnabled(false);
            ui->pushButton_showUpperAverage->setEnabled(false);
            ui->pushButton_sort->setEnabled(false);
            ui->pushButton_show->setEnabled(false);
            QMessageBox::critical(this, "Ошибка", "Выбранный файл не поддерживается");
        }
    }
    else {
        ui->lineEdit->setText("Файл не выбран");
        ui->pushButton_add->setEnabled(false);
        ui->pushButton_change->setEnabled(false);
        ui->pushButton_clear->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_findAverage->setEnabled(false);
        ui->pushButton_findMath->setEnabled(false);
        ui->pushButton_findName->setEnabled(false);
        ui->pushButton_findRus->setEnabled(false);
        ui->pushButton_findPhys->setEnabled(false);
        ui->pushButton_showUpperAverage->setEnabled(false);
        ui->pushButton_sort->setEnabled(false);
        ui->pushButton_show->setEnabled(false);
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int ind = 0;
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_name() == ui->listWidget->currentItem()->text()) {
            ind = i;
            break;
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о абитуриенте");
    window->setGeometry(QRect(450, 350, 800, 250));
    window->resize(650, 10);
    QTableWidget *tableWidget = new QTableWidget();
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(5);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Русский");
            headers1.append("Математика");
            headers1.append("Физика");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    tableWidget->insertRow(0);
    tableWidget->setItem(0, 0, new QTableWidgetItem(abList[ind].get_name()));
    tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(abList[ind].get_rus())));
    tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(abList[ind].get_math())));
    tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(abList[ind].get_phys())));
    tableWidget->setItem(0, 4, new QTableWidgetItem(QString::number(abList[ind].get_average())));
    tableWidget->resizeColumnsToContents();
    window->show();
}


void MainWindow::on_pushButton_show_clicked()
{
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о абитуриентах");
    window->setGeometry(QRect(450, 150, 800, 250));
    window->resize(650, 500);

    QTableWidget *tableWidget = new QTableWidget();
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(5);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Русский");
            headers1.append("Математика");
            headers1.append("Физика");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < abList.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(abList[i].get_name()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(abList[i].get_rus())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(abList[i].get_math())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(abList[i].get_phys())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(abList[i].get_average())));
        tableWidget->resizeColumnsToContents();
    }
    window->show();
}

abiturient newAbitur;

void MainWindow::on_pushButton_add_clicked()
{
    newAbitur.set_name("");
    newAbitur.set_marks(0, 0, 0);
    Dialog win;
    win.setModal(true);
    win.exec();

    if (newAbitur.get_name().length()) {
        abList.addEnd(newAbitur);
        ui->listWidget->addItem(newAbitur.get_name());
        std::fstream file;
        file.open(fileName.toStdString(), std::ios::out | std::ios::app);
        file << "\n" <<  newAbitur.get_name().toStdString() << "\n";
        file << newAbitur.get_marks().toStdString();
        file.close();
    }
}

bool error = false;

void Dialog::on_pushButton_clicked()
{
    try {
        newAbitur.set_name(ui->lineEdit->text().toStdString());
        newAbitur.set_marks(stoi(ui->lineEdit_2->text().toStdString()), stoi(ui->lineEdit_3->text().toStdString()), stoi(ui->lineEdit_4->text().toStdString()));
        window()->close();
        error = false;
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        error = true;
        newAbitur.set_name("");
        newAbitur.set_marks(0, 0, 0);
    }
}

void MainWindow::on_pushButton_delete_clicked()
{
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_name() == ui->listWidget->currentItem()->text()) {
            abList.erase(i);
            break;
        }
    }

    ui->listWidget->clear();

    std::fstream file;
    file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
    for (int i = 0; i < abList.size(); ++i) {
        file <<  abList[i].get_name().toStdString() << "\n";
        file << abList[i].get_marks().toStdString();
        if (i != abList.size() - 1)
            file << "\n";
        ui->listWidget->addItem(abList[i].get_name());
    }
    file.close();
}

void Change(int ind) {
    Dialog win(abList[ind]);
    win.setModal(true);
    win.exec();

    if (!error) {
        abList[ind] = newAbitur;
        std::fstream file;
        file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
        for (int i = 0; i < abList.size(); ++i) {
            file <<  abList[i].get_name().toStdString() << "\n";
            file << abList[i].get_marks().toStdString();
            if (i != abList.size() - 1)
                file << "\n";
        }
        file.close();
    }
}

void MainWindow::on_pushButton_change_clicked()
{
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_name() == ui->listWidget->currentItem()->text()) {
            Change(i);
            ui->listWidget->clear();
            for (int i = 0; i < abList.size(); ++i) {
                ui->listWidget->addItem(abList[i].get_name());
            }
            break;
        }
    }
}


void MainWindow::on_pushButton_showUpperAverage_clicked()
{
    QVector<abiturient> upperAverage;
    double average = 0;
    for (int i = 0; i < abList.size(); ++i) {
        average += abList[i].get_average();
    }
    average /= abList.size();
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_average() > average) {
            upperAverage.push_back(abList[i]);
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о абитуриентах со средним баллом выше среднего по университету");
    window->setGeometry(QRect(450, 150, 800, 250));
    window->resize(650, 500);

    QTableWidget *tableWidget = new QTableWidget();
    QLabel *label = new QLabel();
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 1, 0);
    layout->addWidget(label, 0, 0);

    label->setText("Средний балл по университету: " + QString::number(average));

    tableWidget->setColumnCount(5);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Русский");
            headers1.append("Математика");
            headers1.append("Физика");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < upperAverage.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(upperAverage[i].get_name()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(upperAverage[i].get_rus())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(upperAverage[i].get_math())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(upperAverage[i].get_phys())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(upperAverage[i].get_average())));
        tableWidget->resizeColumnsToContents();
    }
    window->show();
}

bool cmpName(const abiturient& ab1, const abiturient& ab2) {
    QString str1 = ab1.get_name();
    QString str2 = ab2.get_name();
    for (int i = 0; i < ab1.get_name().length() && i < ab2.get_name().length(); ++i) {
        if (str1[i].toLower() < str2[i].toLower()) return true;
        if (str1[i].toLower() > str2[i].toLower()) return false;
    }
    return false;
}

bool cmpAverage(const abiturient& ab1, const abiturient& ab2) {
    for (int i = 0; i < ab1.get_name().length() && i < ab2.get_name().length(); ++i) {
        if (ab1.get_average() < ab2.get_average()) return true;
        if (ab1.get_average() > ab2.get_average()) return false;
    }
    return false;
}

bool eqName(std::string str1, std::string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), tolower);
    transform(str2.begin(), str2.end(), str2.begin(), tolower);
    if (str1.find(str2, 0) != std::string::npos)
        return true;
    else
        return false;
}

bool eqAverage(double ab1, double ab2) {
    double e = 0.5;
    if (ab2 >= ab1 - e && ab2 <= ab1 + e)
        return true;
    return false;
}

void MainWindow::on_pushButton_sort_clicked()
{
    auto arr = new abiturient[abList.size()];
    for (int i = 0; i < abList.size(); ++i) {
        arr[i] = abList[i];
    }
    merge_sort(arr, abList.size(), cmpName);
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
         abList[i] = arr[i];
         ui->listWidget->addItem(abList[i].get_name());
    }
    delete[] arr;
}

QString findName;
double findAverage;
int findRus;
int findMath;
int findPhys;
bool checked;

void MainWindow::on_pushButton_findName_clicked()
{
    checked = false;
    Search name("name");
    name.setModal(true);
    name.exec();

    if (!checked)
        return;
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
        if (eqName(abList[i].get_name().toStdString(), findName.toStdString()))
            ui->listWidget->addItem(abList[i].get_name());
    }
    if (!ui->listWidget->count()) {
        QMessageBox::information(this, "Пусто", "Таких абитуриентов не найдено");
        for (int i = 0; i < abList.size(); ++i) {
            ui->listWidget->addItem(abList[i].get_name());
        }
    }
}

bool kostyl;

void Search::on_pushButton_clicked()
{
    findAverage = findRus = findMath = findPhys = 0;
    findName.clear();
    try {
        if (kostyl) {
            findAverage = stod(ui->lineEdit->text().toStdString());
            findRus = findMath = findPhys = stoi(ui->lineEdit->text().toStdString());
        }
        findName = ui->lineEdit->text();
        if (findName.length()) {
            window()->close();
        }
        checked = true;
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Ошибка ввода");
        ui->lineEdit->clear();
        checked = false;
    }
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
        ui->listWidget->addItem(abList[i].get_name());
    }
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


void MainWindow::on_pushButton_findAverage_clicked()
{
    checked = false;
    Search name("average");
    name.setModal(true);
    name.exec();

    if (!checked)
        return;
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
        if (eqAverage(findAverage, abList[i].get_average()))
            ui->listWidget->addItem(abList[i].get_name());
    }
    if (!ui->listWidget->count()) {
        QMessageBox::information(this, "Пусто", "Таких абитуриентов не найдено");
        for (int i = 0; i < abList.size(); ++i) {
            ui->listWidget->addItem(abList[i].get_name());
        }
    }
}


void MainWindow::on_pushButton_findRus_clicked()
{
    checked = false;
    Search name("rus");
    name.setModal(true);
    name.exec();

    if (!checked)
        return;
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_rus() == findRus)
            ui->listWidget->addItem(abList[i].get_name());
    }
    if (!ui->listWidget->count()) {
        QMessageBox::information(this, "Пусто", "Таких абитуриентов не найдено");
        for (int i = 0; i < abList.size(); ++i) {
            ui->listWidget->addItem(abList[i].get_name());
        }
    }
}


void MainWindow::on_pushButton_findMath_clicked()
{
    checked = false;
    Search name("math");
    name.setModal(true);
    name.exec();

    if (!checked)
        return;
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_math() == findMath)
            ui->listWidget->addItem(abList[i].get_name());
    }
    if (!ui->listWidget->count()) {
        QMessageBox::information(this, "Пусто", "Таких абитуриентов не найдено");
        for (int i = 0; i < abList.size(); ++i) {
            ui->listWidget->addItem(abList[i].get_name());
        }
    }
}


void MainWindow::on_pushButton_findPhys_clicked()
{
    checked = false;
    Search name("phys");
    name.setModal(true);
    name.exec();

    if (!checked)
        return;
    ui->listWidget->clear();
    for (int i = 0; i < abList.size(); ++i) {
        if (abList[i].get_phys() == findPhys)
            ui->listWidget->addItem(abList[i].get_name());
    }
    if (!ui->listWidget->count()) {
        QMessageBox::information(this, "Пусто", "Таких абитуриентов не найдено");
        for (int i = 0; i < abList.size(); ++i) {
            ui->listWidget->addItem(abList[i].get_name());
        }
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_change->setEnabled(true);
    ui->pushButton_delete->setEnabled(true);
}

