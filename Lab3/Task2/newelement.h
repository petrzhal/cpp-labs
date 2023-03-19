#ifndef NEWELEMENT_H
#define NEWELEMENT_H

#include <QDialog>

namespace Ui {
class NewElement;
}

class NewElement : public QDialog
{
    Q_OBJECT

public:
    explicit NewElement(QWidget *parent = nullptr);
    ~NewElement();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_add_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::NewElement *ui;
};

#endif // NEWELEMENT_H
