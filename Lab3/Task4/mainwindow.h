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
    void on_pushButton_add_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_capacity_clicked();

    void on_pushButton_show_clicked();

    void on_pushButton_clicked();

    void on_pushButton_changeSize_clicked();

    void on_pushButton_deleteInd_clicked();

    void on_pushButton_deleteFew_clicked();

    void on_pushButton_popback_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
