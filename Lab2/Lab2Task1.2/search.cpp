#include "search.h"
#include "ui_search.h"
#include <QMessageBox>
#include <string>

extern int findHeight;
extern int findAge;
extern int findNumber;
extern double findWeight;
extern bool checked;

search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
}

search::search(SearchOpenConfig config) :
    ui(new Ui::search)
{
    ui->setupUi(this);
    if (config == SearchOpenConfig::height) {
        window()->setWindowTitle("Поиск по росту");
        ui->label->setText("Введите искомый рост:");
    }
    else if (config == SearchOpenConfig::weight) {
        window()->setWindowTitle("Поиск по весу");
        ui->label->setText("Введите искомый вес:");
    }
    else if (config == SearchOpenConfig::age) {
        window()->setWindowTitle("Поиск по возрасту");
        ui->label->setText("Введите искомый возраст:");
    }
    else if (config == SearchOpenConfig::number) {
        window()->setWindowTitle("Поиск по игровому номеру");
        ui->label->setText("Введите искомый номер:");
    }
}


search::~search()
{
    delete ui;
}

void search::on_pushButton_clicked()
{
    findHeight = 0;
    findAge = 0;
    findNumber = 0;
    findWeight = 0;
    std::string height = ui->lineEdit->text().toStdString();
    std::string weight = ui->lineEdit->text().toStdString();
    std::string number = ui->lineEdit->text().toStdString();
    std::string age = ui->lineEdit->text().toStdString();
    try {
        if (!height.empty()) {
            findHeight = stoi(height);
            findAge = stoi(age);
            findNumber = stoi(number);
            findWeight = stod(weight);
            if (findHeight && findAge && findNumber && findWeight)
                window()->close();
            else {
                QMessageBox::critical(this, "Ошибка", "Некорректные данные");
                ui->lineEdit->clear();
            }
            checked = true;
        }
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
        ui->lineEdit->clear();
        checked = false;
    }
}

