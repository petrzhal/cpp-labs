#ifndef SOLVE_H
#define SOLVE_H
#include "chaintbl.h"
#include <QString>
#include <QVector>

class Solve : public HTable<int, int, 15>
{
private:
    size_t K = 15;
public:
    Solve() = default;
    void CreateRandom(int, int);
    QVector<QString> Stacks();
    void RemoveNegative();
};

#endif // SOLVE_H
