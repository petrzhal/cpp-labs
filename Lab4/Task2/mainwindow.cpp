#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cfunc.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

char a[] = "1234567890";
char b[] = "1234567890";

void MainWindow::on_pushButton_strcpy_clicked()
{
    my_strcpy(a, b);
    ui->textBrowser->append(b);
    ui->textBrowser_res->append(a);
}


void MainWindow::on_pushButton_strncpy_clicked()
{
    my_strncpy(a, b);
    ui->textBrowser->append(b);
    ui->textBrowser_res->append(a);
}


void MainWindow::on_pushButton_memcpy_clicked()
{
    my_memcpy(a, b, 5);
    ui->textBrowser->append(b);
    ui->textBrowser_res->append(a);
}


void MainWindow::on_pushButton_strcat_clicked()
{
    char a[] = "1234567890";
    char b[] = "1234567890";
    my_strcat(b, a);
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(b);
}


void MainWindow::on_pushButton_memmove_clicked()
{
    char a[] = "1234567890";
    char b[] = "1234567890";
    my_memmove(b, a, 4);
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(b);
}


void MainWindow::on_pushButton_strncat_clicked()
{
    char a[] = "1234567890";
    char b[] = "1234567890";
    my_strncat(b, a);
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(b);
}


void MainWindow::on_pushButton_memcmp_clicked()
{
    ui->textBrowser_res->append(QString::number(my_memcmp(b, a, 10)));
    ui->textBrowser->append(a);
    //ui->textBrowser_res->append(b);`1
}

void MainWindow::on_pushButton_strcmp_clicked()
{
    ui->textBrowser_res->append(QString::number(my_strcmp(b, a)));
    ui->textBrowser->append(a);
    //ui->textBrowser_res->append(b);
}


void MainWindow::on_pushButton_strcoll_clicked()
{
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(my_strcoll(b, a));
}


void MainWindow::on_pushButton_strncmp_clicked()
{
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(QString::number(my_strncmp(b, a, 10)));
}


void MainWindow::on_pushButton_strxfrm_clicked()
{

    ui->textBrowser->append(a);
    ui->textBrowser_res->append(QString::number(my_strxfrm(b, a, 10)));
}


void MainWindow::on_pushButton_srtlen_clicked()
{
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(QString::number(my_strlen(a)));
}


void MainWindow::on_pushButton_strtok_clicked()
{
    char a[] = "1/2/3/4/5/6/7/8/9/0";
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(my_strtok(a, '/'));
}


void MainWindow::on_pushButton_memset_clicked()
{
    char* b = new char[11]{};
    b = (char*)my_memset(b, '1', 10);
    b[10] = '\0';
    ui->textBrowser->append(a);
    ui->textBrowser_res->append(b);
}


void MainWindow::on_pushButton_strerror_clicked()
{
    int a = rand() % 40;
    ui->textBrowser->append(QString::number(a));
    ui->textBrowser_res->append(my_strerror(a));
}

