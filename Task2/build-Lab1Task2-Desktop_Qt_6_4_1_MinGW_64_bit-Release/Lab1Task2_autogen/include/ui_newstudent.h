/********************************************************************************
** Form generated from reading UI file 'newstudent.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSTUDENT_H
#define UI_NEWSTUDENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewStudent
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_speciality;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_group;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_form;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_mark1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_mark2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEdit_mark3;

    void setupUi(QDialog *NewStudent)
    {
        if (NewStudent->objectName().isEmpty())
            NewStudent->setObjectName("NewStudent");
        NewStudent->resize(310, 340);
        pushButton = new QPushButton(NewStudent);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(50, 290, 211, 29));
        widget = new QWidget(NewStudent);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 20, 271, 254));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName("lineEdit_name");

        horizontalLayout->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_speciality = new QLineEdit(widget);
        lineEdit_speciality->setObjectName("lineEdit_speciality");

        horizontalLayout_2->addWidget(lineEdit_speciality);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        lineEdit_group = new QLineEdit(widget);
        lineEdit_group->setObjectName("lineEdit_group");

        horizontalLayout_3->addWidget(lineEdit_group);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        lineEdit_form = new QLineEdit(widget);
        lineEdit_form->setObjectName("lineEdit_form");

        horizontalLayout_4->addWidget(lineEdit_form);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        lineEdit_mark1 = new QLineEdit(widget);
        lineEdit_mark1->setObjectName("lineEdit_mark1");

        horizontalLayout_5->addWidget(lineEdit_mark1);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");

        horizontalLayout_6->addWidget(label_6);

        lineEdit_mark2 = new QLineEdit(widget);
        lineEdit_mark2->setObjectName("lineEdit_mark2");

        horizontalLayout_6->addWidget(lineEdit_mark2);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        lineEdit_mark3 = new QLineEdit(widget);
        lineEdit_mark3->setObjectName("lineEdit_mark3");

        horizontalLayout_7->addWidget(lineEdit_mark3);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(NewStudent);

        QMetaObject::connectSlotsByName(NewStudent);
    } // setupUi

    void retranslateUi(QDialog *NewStudent)
    {
        NewStudent->setWindowTitle(QCoreApplication::translate("NewStudent", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260", nullptr));
        pushButton->setText(QCoreApplication::translate("NewStudent", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("NewStudent", "\320\244\320\230\320\236:", nullptr));
        label_2->setText(QCoreApplication::translate("NewStudent", "\320\241\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214:", nullptr));
        label_3->setText(QCoreApplication::translate("NewStudent", "\320\223\321\200\321\203\320\277\320\277\320\260:", nullptr));
        label_4->setText(QCoreApplication::translate("NewStudent", "\320\244\320\276\321\200\320\274\320\260 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217:", nullptr));
        label_5->setText(QCoreApplication::translate("NewStudent", "\320\236\321\202\320\274\320\265\321\202\320\272\320\2601:", nullptr));
        label_6->setText(QCoreApplication::translate("NewStudent", "\320\236\321\202\320\274\320\265\321\202\320\272\320\2602:", nullptr));
        label_7->setText(QCoreApplication::translate("NewStudent", "\320\236\321\202\320\274\320\265\321\202\320\272\320\2603:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewStudent: public Ui_NewStudent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSTUDENT_H
