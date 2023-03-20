#ifndef RESIZE_H
#define RESIZE_H

#include <QDialog>

namespace Ui {
class Resize;
}

class Resize : public QDialog
{
    Q_OBJECT

public:
    explicit Resize(QWidget *parent = nullptr);
    ~Resize();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Resize *ui;
};

#endif // RESIZE_H
