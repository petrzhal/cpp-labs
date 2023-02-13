#ifndef HEIGHT_H
#define HEIGHT_H

#include <QDialog>

namespace Ui {
class Height;
}

class Height : public QDialog
{
    Q_OBJECT

public:
    explicit Height(QWidget *parent = nullptr);
    ~Height();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Height *ui;
};

#endif // HEIGHT_H
