#include "solve.h"
#include <QDebug>

void Solve::CreateRandom(int min, int max)
{
    srand(time(NULL));
    for (int i = 0; i < 500; ++i) {
        int r = rand() % ((max - min) + 1) + min;
        insert(r, 0);
    }
}

QVector<QString> Solve::Stacks()
{
    QVector<QString> stacks;
    for (size_t i = 0; i < K; ++i) {
        QString buf;
        auto tmp = base[i];
        while (!tmp.empty()) {
            buf.append(QString::number(tmp.pop().first) + " ");
        }
        stacks.push_back(buf);
    }
    return stacks;
}

void Solve::RemoveNegative()
{
    for (int i = -100; i < 0; ++i) {
        erase(i);
    }
}
