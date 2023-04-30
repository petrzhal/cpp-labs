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
    void ShowGraphic16();
    void ShowGraphic64();
    void ShowGraphic128();
    void ShowGraphic2048();

private slots:
    void on_pushButton_graphics_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
