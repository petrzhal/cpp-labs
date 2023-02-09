#ifndef NEWSTUDENT_H
#define NEWSTUDENT_H

#include <QDialog>
#include "student.h"

namespace Ui {
class NewStudent;
}

class NewStudent : public QDialog
{
    Q_OBJECT

public:
    explicit NewStudent(QWidget *parent = nullptr);
    explicit NewStudent(const Student&);
    ~NewStudent();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewStudent *ui;
};

#endif // NEWSTUDENT_H
