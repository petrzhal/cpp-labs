#ifndef SOLVE_H
#define SOLVE_H
#include <QString>
#include "queue.h"

class Solve
{
private:
    queue<int> q;
public:
    Solve() = default;
    QString ToString();
    void CreateQueue();
    void DeleteMinMax();
    void Clear();
};

#endif // SOLVE_H
