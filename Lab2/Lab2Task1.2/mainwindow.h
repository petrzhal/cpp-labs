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

    void on_pushButton_showAll_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_listWidget_teams_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_countries_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_teams_itemClicked(QListWidgetItem *item);

    void on_listWidget_countries_itemClicked(QListWidgetItem *item);

    void on_pushButton_showWeight_clicked();

    void on_pushButton_showHeight_clicked();

    void on_lineEdit_nameFilter_textChanged(const QString &arg1);

    void on_lineEdit_teamFilter_textChanged(const QString &arg1);

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_showYoungest_clicked();

    void on_lineEdit_countryFilter_textChanged(const QString &arg1);

    void on_pushButton_clear_clicked();

    void on_pushButton_findHeight_clicked();

    void on_pushButton_findWeight_clicked();

    void on_pushButton_findNum_clicked();

    void on_pushButton_findAge_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
