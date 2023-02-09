/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_nextDay;
    QPushButton *pushButton_5;
    QPushButton *pushButton_isLeap;
    QPushButton *pushButton_edit;
    QPushButton *pushButton_add;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_week;
    QPushButton *pushButton_duration;
    QPushButton *pushButton_daysTillYourBirthday;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_file;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(910, 679);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 50, 91, 201));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setBaseSize(QSize(101, 101));
        QFont font;
        font.setPointSize(11);
        listWidget->setFont(font);
        listWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 250, 91, 31));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(120, 50, 241, 175));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_nextDay = new QPushButton(layoutWidget);
        pushButton_nextDay->setObjectName("pushButton_nextDay");

        verticalLayout->addWidget(pushButton_nextDay);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName("pushButton_5");

        verticalLayout->addWidget(pushButton_5);

        pushButton_isLeap = new QPushButton(layoutWidget);
        pushButton_isLeap->setObjectName("pushButton_isLeap");

        verticalLayout->addWidget(pushButton_isLeap);

        pushButton_edit = new QPushButton(layoutWidget);
        pushButton_edit->setObjectName("pushButton_edit");

        verticalLayout->addWidget(pushButton_edit);

        pushButton_add = new QPushButton(layoutWidget);
        pushButton_add->setObjectName("pushButton_add");

        verticalLayout->addWidget(pushButton_add);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 300, 341, 361));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(layoutWidget1);
        textBrowser->setObjectName("textBrowser");

        verticalLayout_2->addWidget(textBrowser);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        pushButton_week = new QPushButton(layoutWidget1);
        pushButton_week->setObjectName("pushButton_week");

        verticalLayout_3->addWidget(pushButton_week);

        pushButton_duration = new QPushButton(layoutWidget1);
        pushButton_duration->setObjectName("pushButton_duration");

        verticalLayout_3->addWidget(pushButton_duration);

        pushButton_daysTillYourBirthday = new QPushButton(layoutWidget1);
        pushButton_daysTillYourBirthday->setObjectName("pushButton_daysTillYourBirthday");
        pushButton_daysTillYourBirthday->setEnabled(true);

        verticalLayout_3->addWidget(pushButton_daysTillYourBirthday);


        verticalLayout_2->addLayout(verticalLayout_3);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 521, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(10);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton_file = new QPushButton(widget);
        pushButton_file->setObjectName("pushButton_file");

        horizontalLayout->addWidget(pushButton_file);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButton_nextDay->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        pushButton_isLeap->setText(QCoreApplication::translate("MainWindow", "\320\257\320\262\320\273\321\217\320\265\321\202\321\201\321\217 \320\273\320\270 \320\263\320\276\320\264 \320\262\320\270\321\201\320\276\320\272\320\276\321\201\320\275\321\213\320\274", nullptr));
        pushButton_edit->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_week->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\275\320\276\320\274\320\265\321\200 \320\275\320\265\320\264\320\265\320\273\320\270 \320\262 \321\202\320\265\320\272\321\203\321\211\320\265\320\274\n"
" \320\263\320\276\320\264\321\203 \320\264\320\273\321\217 \321\202\320\265\320\272\321\203\321\211\320\265\320\271 \320\264\320\260\321\202\321\213", nullptr));
        pushButton_duration->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\321\214 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\264\320\275\320\265\320\271 \320\274\320\265\320\266\320\264\321\203\n"
"\321\202\320\265\320\272\321\203\321\211\320\265\320\271 \320\264\320\260\321\202\320\276\320\271 \320\270 \320\267\320\260\320\264\320\260\320\275\320\275\320\276\320\271", nullptr));
        pushButton_daysTillYourBirthday->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \321\201\320\272\320\276\320\273\321\214\320\272\320\276 \320\264\320\275\320\265\320\271 \320\264\320\276 \320\262\320\260\321\210\320\265\320\263\320\276 \320\264\320\275\321\217\n"
"\321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217 \320\276\321\202 \321\202\320\265\320\272\321\203\321\211\320\265\320\271 \320\264\320\260\321\202\321\213", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\271 \321\204\320\260\320\271\320\273:", nullptr));
        pushButton_file->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
