#include "mainwindow.h"
#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>

//struct Node {
//    int key;
//    Node *left;
//    Node *right;

//    Node(int k) : key(k), left(nullptr), right(nullptr) {}
//};

//void addNode(Node *node, QTreeWidgetItem *parentItem) {
//    if (!node) return;
//    QTreeWidgetItem *item = new QTreeWidgetItem(parentItem, QStringList(QString::number(node->key)));
//    addNode(node->left, item);
//    addNode(node->right, item);
//}

//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    // Создаем дерево
//    Node *root = new Node(5);
//    root->left = new Node(3);
//    root->left->left = new Node(1);
//    root->left->right = new Node(4);
//    root->right = new Node(7);
//    root->right->left = new Node(6);
//    root->right->right = new Node(8);

//    // Создаем TreeWidget
//    QTreeWidget *treeWidget = new QTreeWidget();
//    treeWidget->setColumnCount(1);

//    QTreeWidgetItem *rootItem = new QTreeWidgetItem(treeWidget);
//    treeWidget->addTopLevelItem(rootItem);

//    // Добавляем узлы дерева
//    addNode(root, rootItem);

//    // Отображаем TreeWidget
//    treeWidget->show();

//    return app.exec();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}







