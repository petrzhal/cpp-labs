#include "solve.h"

QString Solve::ToString()
{
    QString line;
    auto qBuff = q;
    while (!qBuff.empty()) {
        line += QString::number(qBuff.front()) + " ";
        qBuff.pop();
    }
    return line;
}

void Solve::CreateQueue()
{
    q.clear();
    for (int i = 0; i < 20; ++i) {
        q.push(rand() % 20);
    }
}

void Solve::DeleteMinMax()
{
    if (q.empty())
        return;

    int min = q.front(), max = q.front(), numMin = 0, numMax = 0;
    queue<int> qBuf = q;

    for (int i = 0; !qBuf.empty(); i++) {
        if (qBuf.front() < min) {
            min = qBuf.front();
            numMin = i;
        }
        if (qBuf.front() > max) {
            max = qBuf.front();
            numMax = i;
        }
        qBuf.pop();
    }

    if (numMin > numMax) {
        int tmp = numMin;
        numMin = numMax;
        numMax = tmp;
    }

    qBuf.swap(q);
    for (int i = 0; !qBuf.empty(); i++) {
        if (i <= numMin || i >= numMax)
            q.push(qBuf.front());
        qBuf.pop();
    }
}

void Solve::Clear()
{
    q.clear();
}
