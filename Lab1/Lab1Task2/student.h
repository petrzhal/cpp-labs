#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
private:
    std::string speciality;
    std::string name;
    int group;
    std::string form;
    int mark1;
    int mark2;
    int mark3;
    double average;
public:
    Student();
    Student(const Student&);

    void set_name(const std::string&);
    void set_speciality(const std::string&);
    void set_group(int);
    void set_form(const std::string&);
    void set_marks(int, int, int);

    std::string get_name() const;
    std::string get_speciality() const;
    QString get_group() const;
    QString get_form() const;
    QString get_marks() const;
    int get_mark1() const;
    int get_mark2() const;
    int get_mark3() const;
    QString get_average() const;

    QString toQString() const;

    Student& operator=(const Student&);
};
#endif // STUDENT_H
