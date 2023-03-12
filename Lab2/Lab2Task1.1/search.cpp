#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
}

extern bool kostyl;

Search::Search(const QString& str) : ui(new Ui::Search)
{
    ui->setupUi(this);
    if (str == "name") {
        ui->label->setText("Введите искомое ФИО");
        kostyl = false;
        window()->setWindowTitle("Поиск по ФИО");
    }
    else if (str == "average") {
        ui->label->setText("Введите искомый средний балл");
        kostyl = true;
        window()->setWindowTitle("Поиск по среднему баллу");
    }
    else if (str == "rus") {
        ui->label->setText("Введите искомый балл по русскому");
        kostyl = true;
        window()->setWindowTitle("Поиск по русскому");
    }
    else if (str == "math") {
        ui->label->setText("Введите искомый балл по математике");
        kostyl = true;
        window()->setWindowTitle("Поиск по математике");
    }
    else if (str == "phys") {
        ui->label->setText("Введите искомый балл по физике");
        kostyl = true;
        window()->setWindowTitle("Поиск по физике");
    }
}

Search::~Search()
{
    delete ui;
}


