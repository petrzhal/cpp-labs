/********************************************************************************
** Form generated from reading UI file 'birthdayinput.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIRTHDAYINPUT_H
#define UI_BIRTHDAYINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BirthdayInput
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *BirthdayInput)
    {
        if (BirthdayInput->objectName().isEmpty())
            BirthdayInput->setObjectName("BirthdayInput");
        BirthdayInput->resize(460, 341);
        groupBox = new QGroupBox(BirthdayInput);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(80, 50, 301, 231));
        widget = new QWidget(BirthdayInput);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(130, 120, 196, 116));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        retranslateUi(BirthdayInput);

        QMetaObject::connectSlotsByName(BirthdayInput);
    } // setupUi

    void retranslateUi(QDialog *BirthdayInput)
    {
        BirthdayInput->setWindowTitle(QCoreApplication::translate("BirthdayInput", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("BirthdayInput", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\321\202\321\203 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        pushButton->setText(QCoreApplication::translate("BirthdayInput", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BirthdayInput: public Ui_BirthdayInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIRTHDAYINPUT_H
