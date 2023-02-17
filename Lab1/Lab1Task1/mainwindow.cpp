#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "vector.cpp"
#include <QDebug>
#include <ctime>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QTextEdit>
#include <fstream>
#include <QObject>
#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->textBrowser->setFontPointSize(11);        
    ui->pushButton_isLeap->setEnabled(false);
    ui->pushButton_nextDay->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_add->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class Date {
    int day, month, year;

public:
    Date() {
        day = month = year = 0;
    }

    Date(const Date& date) {
        year = date.year;
        month = date.month;
        day = date.day;
    }

    int get_year() const;
    int get_month() const;
    int get_day() const;

    Date PreviousDay();

    void Normalize();

    void InputValidation();

    Date NextDay();

    void ScanFile();

    friend Date fromStdString(const std::string&);

    QString ToQString();

    int ToDays();

    bool IsLeap();

    Date operator=(const Date& date) {
        year = date.year;
        month = date.month;
        day = date.day;
        return *this;
    }
};

vector<Date> dates;
std::string birthday;
std::string dateIn;

int Date::get_year() const {
    return year;
}

int Date::get_month() const {
    return month;
}

int Date::get_day() const {
    return day;
}

Date fromStdString(const std::string& date) {
    Date newDate;
    newDate.year = stoi(date.substr(6, 4));
    newDate.month = stoi(date.substr(3, 2));
    newDate.day = stoi(date.substr(0, 2));

    return newDate;
}

bool ISLeap(int year) {
    if ((!(year % 4) && (year % 100)) || !(year % 400)) {
        return true;
    }
    return false;
}

bool Date::IsLeap() {
    if ((!(year % 4) && (year % 100)) || !(year % 400)) {
        return true;
    }
    return false;
}

QString Date::ToQString() {
    QString date;
    date += (day > 9 ? QString::number(day) : "0" + QString::number(day)) + "." + (month > 9 ? QString::number(month) : "0" + QString::number(month)) + "." + (year > 999 ? QString::number(year) : (year > 99 ? "0" + QString::number(year) : ((year > 9 ? "00" + QString::number(year) : "000" + QString::number(year)))));
    return date;
}

void Date::Normalize() {
    if (month > 12) {
        year += month / 12;
        month %= 12;
    }

    if (month == 2) {
        if ((!(year % 4) && (year % 100)) || !(year % 400)) {
            if (day > 29) {
                month += day / 29;
                day %= 29;
            }          
        }
        else {
            if (day > 28) {
                month += day / 28;
                day %= 28;
            }
        }
    }
    else if (month == 1 || month == 3  || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day > 31) {
            month += day / 31;
            day %= 31;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11){

        if (day > 30) {
            month += day / 30;
            day %= 30;
        }
    }

    if (month > 12) {
        year += month / 12;
        month %= 12;
    }

    if (day <= 0) {
        if (month == 2 || month == 1 || month == 4 || month == 6 || month == 9 || month == 11 || month == 8) {
            month--;
            day = 31;
        }
        else if (month == 5 || month == 7 || month == 10 || month == 12) {
            month--;
            day = 30;
        }
        else if (month == 3) {
            if (ISLeap(year))
                day = 29;
            else
                day = 28;
            month--;
        }
    }

    if (month <= 0) {
        month = 12;
        year--;
    }
}

void Date::InputValidation() {
    if (month > 12 || month <= 0 || day <= 0 || year <= 0) {
        day = month = year = 0;
        throw "Invalid date";
    }

    if (month == 2) {
        if ((!(year % 4) && (year % 100)) || !(year % 400)) {
            if (day > 29) {
                day = month = year = 0;
                throw "Invalid date";
            }
        }
        else {
            if (day > 28) {
                day = month = year = 0;
                throw "Invalid date";
            }
        }
    }
    else if (month == 1 || month == 3  || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day > 31) {
            day = month = year = 0;
            throw "Invalid date";
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            day = month = year = 0;
            throw "Invalid date";
        }
    }
}

int Date::ToDays() {
    int days = 0;
    int monthA[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 1; i < year; ++i) {
        if (ISLeap(i))
            days += 366;
        else
            days += 365;
    }

    for (int i = 0; i < month - 1; ++i) {
        if (ISLeap(year) && i == 1)
            days += monthA[i] + 1;
        else
            days += monthA[i];
    }

    days += day;

    return days;
}

Date Date::NextDay() {
    Date nextDay = *this;
    nextDay.day++;
    nextDay.Normalize();
    return nextDay;
}

Date Date::PreviousDay() {
    Date previousDay = *this;
    previousDay.day--;
    previousDay.Normalize();
    return previousDay;
}

void CheckDate(const std::string& date) {
    if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[3]) || !isdigit(date[4]) || !isdigit(date[6]) || !isdigit(date[7]) && !isdigit(date[8]) || !isdigit(date[9]) || date[2] != '.' || date[5] != '.' || date.length() != 10) {
        throw "Invalid Date";
    }
}

QString fileName;


void Show(QTableWidget* tableWidget) {
    tableWidget->move(QPoint(380, 50));
    tableWidget->resize(511, 611);
    tableWidget->show();
    tableWidget->setColumnCount(3);
    tableWidget->setShowGrid(true);
    QStringList headers;
            headers.append("Дата");
            headers.append("Следующий день");
            headers.append("Разница между текущим и \nследующим элементом в днях");
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    tableWidget->resizeColumnsToContents();
    for (int i = 0; i < dates.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(dates[i].ToQString()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(dates[i].NextDay().ToQString()));
        if (i != dates.size() - 1)
            tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(abs(dates[i].ToDays() - dates[i + 1].ToDays()))));
        else
            tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(abs(dates[i].ToDays() - dates[0].ToDays()))));
        tableWidget->resizeColumnsToContents();
    }
}

QTableWidget *tableWidget;

void MainWindow::ScanFile() {
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Docs (*.txt)"));
    try {
        std::fstream file;
        file.open(fileName.toStdString(), std::ios::in);
        if (fileName.length())
            if (!file.is_open())
                throw "Invalid file";
        dates.clear();

        try {
            while(file.peek() != EOF) {
                std::string date;
                file >> date;
                Date check = fromStdString(date);
                check.InputValidation();
                CheckDate(date);
                dates.push_back(fromStdString(date));
            }
        }
        catch (...) {
            QMessageBox::critical(this, "Ошибка чтения файла", "В выбранном файле нарушен\nформат записи даты");
            fileName.clear();
            dates.clear();
        }
        ui->lineEdit->setText(fileName);
        ui->textBrowser->clear();

        for (auto& var : dates) {
            var.Normalize();
        }

        file.close();

        ui->listWidget->clear();
        for (auto& var : dates) {
            ui->listWidget->addItem(var.ToQString());
        }
        delete tableWidget;
        tableWidget = new QTableWidget(this);
        if (fileName.length()) {
            ui->pushButton_add->setEnabled(true);
            Show(tableWidget);
        }
        else {
            ui->lineEdit->setText("Файл не выбран");
            ui->pushButton_add->setEnabled(false);
            ui->pushButton_isLeap->setEnabled(false);
            ui->pushButton_nextDay->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            ui->listWidget->clear();
            ui->pushButton->setEnabled(false);
            ui->pushButton_edit->setEnabled(false);
            ui->pushButton_delete->setEnabled(false);
        }
    } catch (...) {
        QMessageBox::critical(this, "Ошибка чтения файла", "Выбранный файл не поддерживается");
        fileName.clear();
        dates.clear();
        ui->lineEdit->setText("Файл не выбран");
        ui->pushButton_add->setEnabled(false);
        ui->pushButton_isLeap->setEnabled(false);
        ui->pushButton_nextDay->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->listWidget->clear();
        ui->pushButton->setEnabled(false);
        ui->pushButton_edit->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
    }
}

void MainWindow::on_pushButton_file_clicked()
{
    ScanFile();
}


std::string currentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %X", now);
    return buffer;
}


qint64 Duration() {
    std::string cDate = currentDateTime().substr(0, 10);
    QDate curDate( stoi(cDate.substr(6, 4)), stoi(cDate.substr(3, 2)), stoi(cDate.substr(0, 2)));
    QDate date2( stoi(dateIn.substr(6, 4)), stoi(dateIn.substr(3, 2)), stoi(dateIn.substr(0, 2)));
    return curDate.daysTo(date2);
}


void MainWindow::on_pushButton_nextDay_clicked()
{    
    ui->textBrowser->clear();
    Date curDate = fromStdString(ui->listWidget->currentItem()->text().toStdString());
    ui->textBrowser->setText("Дата: " + curDate.ToQString() + "  Следующий день: " + curDate.NextDay().ToQString());
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser->clear();
    Date curDate = fromStdString(ui->listWidget->currentItem()->text().toStdString());
    ui->textBrowser->append("Дата: " + curDate.ToQString() + "  Предыдущий день: " + curDate.PreviousDay().ToQString());
}


qint64 DaysTillYourBithday() {
    std::string cDate = currentDateTime().substr(0, 10);
    std::string birthDate = dateIn;
    if (birthDate.substr(0, 5) == "29.02")
        birthDate.replace(0, 5, "01.03");
    if ( stoi(cDate.substr(3, 2)) < stoi(birthDate.substr(3, 2)) ) {
        birthDate.replace(6, 4, "2023");
    }
    else if ( stoi(cDate.substr(3, 2)) == stoi(birthDate.substr(3, 2)) ) {
        if ( stoi(cDate.substr(0, 2)) < stoi(birthDate.substr(0, 2)) ) {
            birthDate.replace(6, 4, "2023");
        }
        else {
            birthDate.replace(6, 4, "2024");
        }
    }
    else {
        birthDate.replace(6, 4, "2024");
    }
    QDate date(stoi(cDate.substr(6, 4)), stoi(cDate.substr(3, 2)), stoi(cDate.substr(0, 2)));
    QDate birth(stoi(birthDate.substr(6, 4)), stoi(birthDate.substr(3, 2)), stoi(birthDate.substr(0, 2)));

    return date.daysTo(birth);
}


void MainWindow::on_pushButton_daysTillYourBirthday_clicked()
{
    Dialog b("Введите дату рождения");
    b.setModal(true);
    b.exec();
    birthday = dateIn;
    try  {
        ui->textBrowser->setText("Дней до вашего дня рождения: " + QString::number(DaysTillYourBithday()));
    }
    catch (...) {}

}

void MainWindow::on_pushButton_isLeap_clicked()
{
    Date var = fromStdString(ui->listWidget->currentItem()->text().toStdString());
    ui->textBrowser->setText(QString::number(var.get_year()) + " год " + (ISLeap(var.get_year()) ? "високосный" : "не високосный"));
}


void MainWindow::on_pushButton_duration_clicked()
{
    Dialog b;
    b.setModal(true);
    b.exec();

    std::string cDate = currentDateTime().substr(0, 10);

    try  {
        ui->textBrowser->setText("Количество дней между " + QString::fromStdString(cDate) + " и " + QString::fromStdString(dateIn) + " :  " + QString::number(abs(Duration())));
    }
    catch (...) {}
}

void Dialog::on_pushButton_clicked()
{
    try {
        CheckDate(ui->lineEdit->text().toStdString());
        dateIn = ui->lineEdit->text().toStdString();
        Date date = fromStdString(dateIn);
        date.InputValidation();
        window()->close();
    }
    catch (...) {
        ui->lineEdit->clear();
        dateIn = "";
        QMessageBox::critical(this, "Ошибка", "Некоректная дата");
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_isLeap->setEnabled(true);
    ui->pushButton_nextDay->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_delete->setEnabled(true);
}



void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    ui->pushButton_edit->setEnabled(false);
    ui->listWidget->currentItem()->setSelected(false);
    ui->pushButton_isLeap->setEnabled(false);
    ui->pushButton_nextDay->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


int WeekNum() {
    std::string cDate = currentDateTime();
    cDate.replace(6, 4, "0000");
    Date curDate = fromStdString(cDate);
    return curDate.ToDays() / 7 + 1;
}

void MainWindow::on_pushButton_week_clicked()
{
    ui->textBrowser->setText("Номер недели для текущей даты: " + QString::number(WeekNum()));
}

void MainWindow::on_pushButton_edit_clicked()
{
    std::fstream file;

    dateIn = "";
    Dialog asd("Введите новую дату");
    asd.setModal(true);
    asd.exec();

    try {
        Date date = fromStdString(dateIn);
        date.InputValidation();
        CheckDate(dateIn);
        file.open(fileName.toStdString(), std::ios::in | std::ios::out);

        int i = ui->listWidget->currentRow();
        file.seekp(12 * i, std::ios::beg);
        file.write(dateIn.c_str(), 10);
        dates[i] = fromStdString(dateIn);
        file.close();

        ui->listWidget->clear();

        for (auto& var : dates) {
            ui->listWidget->addItem(var.ToQString());
        }

        delete tableWidget;
        tableWidget = new QTableWidget(this);
        Show(tableWidget);
    }
    catch (...) {}

    ui->textBrowser->clear();
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_isLeap->setEnabled(false);
    ui->pushButton_nextDay->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


void MainWindow::on_pushButton_add_clicked()
{
    dateIn = "";
    Dialog w("Введите добавляемую дату");
    w.setModal(true);
    w.exec();

    try {
        CheckDate(dateIn);
        dates.push_back(fromStdString(dateIn));

        std::fstream file;
        file.open(fileName.toStdString(), std::ios::app | std::ios::out);
        file << "\n" << dateIn;
        file.close();

        ui->listWidget->clear();

        for (auto& var : dates) {
            ui->listWidget->addItem(var.ToQString());
        }

        delete tableWidget;
        tableWidget = new QTableWidget(this);
        Show(tableWidget);
    }
    catch (...) {}
    ui->textBrowser->clear();
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_isLeap->setEnabled(false);
    ui->pushButton_nextDay->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


void MainWindow::on_pushButton_delete_clicked()
{
    std::fstream file;
    for (int i = 0; i < dates.size(); ++i) {
        if (dates[i].ToQString() == ui->listWidget->currentItem()->text()) {
            dates.erase(i);
        }
    }
    file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
    for (int i = 0; i < dates.size(); ++i) {
        file << dates[i].ToQString().toStdString();
        if (i != dates.size() - 1)
            file << "\n";
    }
    file.close();

    delete tableWidget;
    tableWidget = new QTableWidget(this);
    Show(tableWidget);

    ui->listWidget->clear();

    for (auto& var : dates) {
        ui->listWidget->addItem(var.ToQString());
    }
    ui->textBrowser->clear();
    ui->pushButton_edit->setEnabled(false);
    ui->pushButton_isLeap->setEnabled(false);
    ui->pushButton_nextDay->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

