#ifndef ABITURIENT_H
#define ABITURIENT_H
#include <QApplication>

class abiturient
{
private:
    QString name;
    int rus;
    int math;
    int phys;
    double average;
public:
    abiturient();
    abiturient(const abiturient&);
    void set_name(const std::string&);
    void set_marks(int, int, int);
    QString get_name() const;
    QString get_marks() const;
    int get_rus() const;
    int get_math() const;
    int get_phys() const;
    double get_average() const;
    abiturient& operator=(const abiturient&);
};

#endif // ABITURIENT_H
