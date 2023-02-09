#pragma once
#ifndef BIRTHDAYINPUT_H
#define BIRTHDAYINPUT_H

#include <QDialog>

namespace Ui {
class BirthdayInput;
}

class BirthdayInput : public QDialog
{
    Q_OBJECT

public:
    friend class MainWindow;
    explicit BirthdayInput(QWidget *parent = nullptr);
    ~BirthdayInput();

private slots:
    void on_pushButton_clicked();


protected:
    Ui::BirthdayInput *ui;    
signals:
    void k();
};

#endif // BIRTHDAYINPUT_H
