#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_push_front_clicked();

    void on_pushButton_push_back_clicked();

    void on_pushButton_pop_front_clicked();

    void on_pushButton_pop_back_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_size_clicked();

    void on_pushButton_capacity_clicked();

    void on_pushButton_empty_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
