#include "solve.h"
#include <QString>

extern QString preOrderOut;
extern QString postOrderOut;
extern QString inOrderOut;

void Solve::DeleteBranchWithKey(int key)
{
    root = removeSubtree(root, key);
}

void Solve::inOrder(Node *node) {
    if (!node)
        return;
    inOrder(node->left);
    inOrderOut.push_back(QString::number(node->key) + " ");
    inOrder(node->right);
}

void Solve::postOrder(Node *node) {
    if (!node)
        return;
    postOrder(node->left);
    postOrder(node->right);
    postOrderOut.push_back(QString::number(node->key) + " ");
}

void Solve::preOrder(Node *node) {
    if (!node)
        return;
    preOrderOut.push_back(QString::number(node->key) + " ");
    preOrder(node->left);
    preOrder(node->right);
}
