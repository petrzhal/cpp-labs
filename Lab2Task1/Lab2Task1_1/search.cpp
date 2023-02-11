#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
}

Search::Search(const QString& str) : ui(new Ui::Search)
{
    ui->setupUi(this);
    if (str == "name") {
        ui->label->setText("Введите искомое ФИО");
        window()->setWindowTitle("Поиск по ФИО");
    }
    else if (str == "average") {
        ui->label->setText("Введите искомый средний балл");
        window()->setWindowTitle("Поиск по среднему баллу");
    }
    else if (str == "rus") {
        ui->label->setText("Введите искомый балл по русскому");
        window()->setWindowTitle("Поиск по русскому");
    }
    else if (str == "math") {
        ui->label->setText("Введите искомый балл по математике");
        window()->setWindowTitle("Поиск по математике");
    }
    else if (str == "phys") {
        ui->label->setText("Введите искомый балл по физике");
        window()->setWindowTitle("Поиск по физике");
    }
}

Search::~Search()
{
    delete ui;
}


