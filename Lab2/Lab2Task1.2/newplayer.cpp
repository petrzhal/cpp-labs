#include "newplayer.h"
#include "ui_newplayer.h"
#include "member.h"
#include <QMessageBox>

extern Member Player;

NewPlayer::NewPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPlayer)
{
    ui->setupUi(this);
}

NewPlayer::NewPlayer(FormCreationConfig Config) :
    ui(new Ui::NewPlayer)
{
    ui->setupUi(this);
    if (Config == FormCreationConfig::Add) {
        ui->label_Title->setText("Введите добавляемого участника");
        this->setWindowTitle("Добавление участника");
    }
    else if (Config == FormCreationConfig::Change) {
        ui->label_Title->setText("Изменение данных участника");
        this->setWindowTitle("Изменение участника");
        ui->lineEdit_country->setText(QString::fromStdString(Player.get_country()));
        ui->lineEdit_team->setText(QString::fromStdString(Player.get_team()));
        ui->lineEdit_name->setText(QString::fromStdString(Player.get_name()));
        ui->lineEdit_number->setText(QString::number(Player.get_number()));
        ui->lineEdit_age->setText(QString::number(Player.get_age()));
        ui->lineEdit_height->setText(QString::number(Player.get_height()));
        ui->lineEdit_weight->setText(QString::number(Player.get_weight()));
    }
}

NewPlayer::~NewPlayer()
{
    delete ui;
}

void NewPlayer::on_pushButton_confirm_clicked()
{
    std::string country = ui->lineEdit_country->text().toStdString();
    std::string team = ui->lineEdit_team->text().toStdString();
    std::string name = ui->lineEdit_name->text().toStdString();
    int num = ui->lineEdit_number->text().toInt();
    int age = ui->lineEdit_age->text().toInt();
    int height = ui->lineEdit_height->text().toInt();
    double weight = ui->lineEdit_weight->text().toDouble();
    try {
        if (country.empty() || team.empty() || name.empty())
            throw "Invalid player";
        Player.set_country(country);
        Player.set_team(team);
        Player.set_name(name);
        Player.set_number(num);
        Player.set_age(age);
        Player.set_height(height);
        Player.set_weight(weight);
        window()->close();
    } catch (...) {
        QMessageBox::critical(this, "Ошибка", "Некорректные данные");
    }
}
