#include "student.h"

Student::Student() {
    group = 0;
    mark1 = 0;
    mark2 = 0;
    mark3 = 0;
    average = 0;
}

Student::Student(const Student& student)
{
    speciality = student.speciality;
    name = student.name;
    group = student.group;
    mark1 = student.mark1;
    mark2 = student.mark2;
    mark3 = student.mark3;
    average = student.average;
    form = student.form;
}

Student& Student::operator=(const Student& student) {
    speciality = student.speciality;
    name = student.name;
    group = student.group;
    mark1 = student.mark1;
    mark2 = student.mark2;
    mark3 = student.mark3;
    average = student.average;
    form = student.form;
    return *this;
}

QString Student::toQString() const {
    std::string strName(name);
    std::string strSpec(speciality);
    return QString::fromStdString(strName) + " " + QString::fromStdString(strSpec) + " " + this->get_group() + " " + this->get_form() + " " + this->get_marks() + " " + this->get_average();
}

void Student::set_name(const std::string& name) {
    this->name = name;
}

void Student::set_speciality(const std::string& speciality) {
        this->speciality = speciality;
}

void Student::set_group(int group) {
    this->group = group;
}

void Student::set_form(const std::string& form) {
    if (form != "платное" && form != "бюджет")
        throw "Invalid form";
    this->form = form;
}

void Student::set_marks(int a, int b, int c) {
    mark1 = a;
    mark2 = b;
    mark3 = c;
    average = (a + b + c) / 3.0;
}

std::string Student::get_name() const {
    return name;
}

std::string Student::get_speciality() const {
    return speciality;
}

QString Student::get_group() const {
    return QString::number(group);
}

QString Student::get_form() const {
    return QString::fromStdString(form);
}

QString Student::get_marks() const {
    return (QString::number(mark1) + " " + QString::number(mark2) + " " + QString::number(mark3));
}

QString Student::get_average() const {
    return QString::number(average);
}

int Student::get_mark1() const {
    return mark1;
}

int Student::get_mark2() const {
    return mark2;
}

int Student::get_mark3() const {
    return mark3;
}
