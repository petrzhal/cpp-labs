#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_pushButton_chooseFile_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_show_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_change_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_showUpperAverage_clicked();

    void on_pushButton_sort_clicked();

    void on_pushButton_findName_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_findAverage_clicked();

    void on_pushButton_findRus_clicked();

    void on_pushButton_findMath_clicked();

    void on_pushButton_findPhys_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
