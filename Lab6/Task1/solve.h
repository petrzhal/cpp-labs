#ifndef SOLVE_H
#define SOLVE_H
#include <QString>
#include <QTreeWidget>
#include "bst.h"
#include "mainwindow.h"

class Solve : public AVLTree<int, QString>
{
private:
    void preOrder(Node *);
    void postOrder(Node *);
    void inOrder(Node *);
public:
    friend class MainWindow;
    Solve() = default;
    static void addNode(AVLTree<int, QString>::Node *node, QTreeWidgetItem *parentItem) {
        if (!node) return;
        QTreeWidgetItem *item = new QTreeWidgetItem(parentItem, QStringList(QString::number(node->key)));
        addNode(node->left, item);
        addNode(node->right, item);
    }
    void DeleteBranchWithKey(int key);
    void preOrder() {
        preOrder(root);
    }
    void postOrder() {
        postOrder(root);
    }
    void inOrder() {
        inOrder(root);
    }
};

#endif // SOLVE_H
