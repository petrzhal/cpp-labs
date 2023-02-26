#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
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
    void on_pushButton_clicked();

    void on_pushButton_addExpr_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_pushButton_changeExpr_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
