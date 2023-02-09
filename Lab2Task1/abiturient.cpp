#include "abiturient.h"

abiturient::abiturient()
{
    rus = math = phys = 0;
}

abiturient::abiturient(const abiturient& other) {
    name = other.name;
    rus = other.rus;
    math = other.math;
    phys = other.phys;
    average = other.average;
}

void abiturient::set_name(const std::string& name) {
    this->name = QString::fromStdString(name);
}

void abiturient::set_marks(int rus, int math, int phys) {
    this->rus = rus;
    this->math = math;
    this->phys = phys;
    average = (rus + math + phys) / 3.0;
}

QString abiturient::get_name() const {
    return name;
}

QString abiturient::get_marks() const {
    return QString::number(rus) + " " + QString::number(math) + " " + QString::number(phys);
}

int abiturient::get_rus() const {
    return rus;
}

int abiturient::get_math() const {
    return math;
}

int abiturient::get_phys() const {
    return phys;
}

double abiturient::get_average() const {
    return average;
}

abiturient& abiturient::operator=(const abiturient& other) {
    name = other.name;
    rus = other.rus;
    math = other.math;
    phys = other.phys;
    average = other.average;
    return *this;
}
