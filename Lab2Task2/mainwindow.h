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
    void on_open_triggered();

    void on_save_triggered();

    void on_save_as_triggered();

    void on_textEdit_textChanged();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
