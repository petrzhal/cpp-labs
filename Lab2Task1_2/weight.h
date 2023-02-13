#ifndef WEIGHT_H
#define WEIGHT_H

#include <QDialog>

namespace Ui {
class Weight;
}

class Weight : public QDialog
{
    Q_OBJECT

public:
    explicit Weight(QWidget *parent = nullptr);
    explicit Weight(const QString&);
    ~Weight();

private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::Weight *ui;
};

#endif // WEIGHT_H
