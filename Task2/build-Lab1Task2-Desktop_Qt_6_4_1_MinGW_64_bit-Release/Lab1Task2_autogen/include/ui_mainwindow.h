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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_fileOpen;
    QPushButton *pushButton_add;
    QPushButton *pushButton;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_paid;
    QPushButton *pushButton_2;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget;
    QPushButton *pushButton_showInformation;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_change;
    QPushButton *pushButton_clear;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(580, 660);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(580, 660));
        MainWindow->setMaximumSize(QSize(580, 660));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 30, 281, 241));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 40, 241, 185));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        pushButton_fileOpen = new QPushButton(layoutWidget);
        pushButton_fileOpen->setObjectName("pushButton_fileOpen");
        pushButton_fileOpen->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(pushButton_fileOpen);

        pushButton_add = new QPushButton(layoutWidget);
        pushButton_add->setObjectName("pushButton_add");
        pushButton_add->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(pushButton_add);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(pushButton);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 30, 239, 20));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 280, 281, 161));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 40, 241, 103));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_4->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_4->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(layoutWidget1);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_4->addWidget(pushButton_5);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 450, 281, 191));
        layoutWidget2 = new QWidget(groupBox_3);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(20, 40, 241, 131));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_paid = new QPushButton(layoutWidget2);
        pushButton_paid->setObjectName("pushButton_paid");
        pushButton_paid->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton_paid);

        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton_2);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(310, 40, 251, 581));
        verticalLayout_3 = new QVBoxLayout(layoutWidget3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(layoutWidget3);
        listWidget->setObjectName("listWidget");
        QFont font;
        font.setPointSize(11);
        listWidget->setFont(font);
        listWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        listWidget->setLayoutDirection(Qt::LeftToRight);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_3->addWidget(listWidget);

        pushButton_showInformation = new QPushButton(layoutWidget3);
        pushButton_showInformation->setObjectName("pushButton_showInformation");
        pushButton_showInformation->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(pushButton_showInformation);

        pushButton_delete = new QPushButton(layoutWidget3);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(pushButton_delete);

        pushButton_change = new QPushButton(layoutWidget3);
        pushButton_change->setObjectName("pushButton_change");
        pushButton_change->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(pushButton_change);

        pushButton_clear = new QPushButton(layoutWidget3);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(pushButton_clear);

        MainWindow->setCentralWidget(centralwidget);
        layoutWidget3->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Task2", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \321\204\320\260\320\271\320\273\320\276\320\274", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\277\320\276\320\272\320\260\320\267\320\260\320\275 \320\277\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203", nullptr));
        pushButton_fileOpen->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\262 \320\263\321\200\321\203\320\277\320\277\320\260\321\205 \n"
"\321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\276\320\262 \320\277\320\276 \320\244\320\230\320\236", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\271 \321\204\320\260\320\271\320\273:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214 \320\277\320\276 \320\244\320\230\320\236", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214 \320\277\320\276 \320\275\320\276\320\274\320\265\321\200\321\203 \320\263\321\200\321\203\320\277\320\277\321\213", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214 \320\277\320\276 \321\204\320\276\321\200\320\274\320\265 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\321\217 \320\270\320\267 \320\262\320\260\321\200\320\270\320\260\320\275\321\202\320\260", nullptr));
        pushButton_paid->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\276\320\262 \320\262 \321\200\320\260\320\267\321\200\320\265\320\267\320\265 \n"
"\321\204\320\276\321\200\320\274\321\213 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217 \320\262 \320\277\320\276\321\200\321\217\320\264\320\272\320\265\n"
" \321\203\320\261\321\213\320\262\320\260\320\275\320\270\321\217 \321\201\321\200\320\265\320\264\320\275\320\265\320\263\320\276 \320\261\320\260\320\273\320\273\320\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\276\321\202\320\273\320\270\321\207\320\275\320\270\320\272\320\276\320\262 \320\264\320\273\321\217\n"
" \320\277\320\273\320\260\321\202\320\275\320\276\320\271 \321\204\320\276\321\200\320\274\321\213 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        pushButton_showInformation->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\216\n"
" \320\276 \320\262\321\201\320\265\321\205 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260\321\205", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButton_change->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
