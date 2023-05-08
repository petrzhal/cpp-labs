#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <memory>
#include "node.h"

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
    static void addNode(std::shared_ptr<Node<int, QString>>& node, QTreeWidgetItem *parentItem) {
        if (!node) {
            return;
        }
        QTreeWidgetItem *item = new QTreeWidgetItem(parentItem, QStringList(node->data.second + (node->color == Color::Red ? " R" : " B")));
        addNode(node->left, item);
        addNode(node->right, item);
    }
private slots:
    void on_pushButton_deleteKey_clicked();

    void on_pushButton_insert_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
