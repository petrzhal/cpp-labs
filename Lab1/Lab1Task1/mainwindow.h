#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Date;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ScanFile();
    void HideAll();
    void ShowAll();
protected:
    Ui::MainWindow *ui;
private slots:
    void on_pushButton_file_clicked();    
    void on_pushButton_nextDay_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_isLeap_clicked();
    void on_pushButton_duration_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_clicked();    
    void on_pushButton_week_clicked();
    void on_pushButton_daysTillYourBirthday_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
};

#endif // MAINWINDOW_H

