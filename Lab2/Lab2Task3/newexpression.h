#ifndef NEWEXPRESSION_H
#define NEWEXPRESSION_H

#include <QDialog>

namespace Ui {
class NewExpression;
}

class NewExpression : public QDialog
{
    Q_OBJECT

public:
    explicit NewExpression(QWidget *parent = nullptr);
    ~NewExpression();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewExpression *ui;
};

#endif // NEWEXPRESSION_H
