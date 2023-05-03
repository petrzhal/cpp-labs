#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ShowTree();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_remove_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_add_clicked();

    void on_pushButton_removeKey_clicked();

    void on_pushButton_preOrder_clicked();

    void on_pushButton_postOrder_clicked();

    void on_pushButton_order_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
