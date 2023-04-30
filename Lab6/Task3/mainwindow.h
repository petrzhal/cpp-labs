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
    void Show();

private slots:
    void on_pushButton_create_clicked();

    void on_pushButton_removeNegative_clicked();

    void on_pushButton_random_clicked();

    void on_pushButton_remove_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
