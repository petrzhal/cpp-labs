#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "vector.cpp"
#include "student.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "newstudent.h"
#include "ui_newstudent.h"
#include <fstream>
#include <QDebug>
#include <QFileDialog>
#include <QTextEdit>
#include <algorithm>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    ui->pushButton_showInformation->setEnabled(false);
    ui->pushButton_paid->setEnabled(false);    
    ui->pushButton_add->setEnabled(false);
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString fileName;
vector<Student> students;

void MainWindow::on_pushButton_fileOpen_clicked()
{
    ui->listWidget->clear();
    students.clear();

    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Text Docs (*.txt)"));

    try {
        std::fstream file;
        file.open(fileName.toStdString(), std::ios::in | std::ios::out);
        if (!file.is_open())
            throw "Invalid file";
        for (int i = 0; file.peek() != EOF; ++i) {
            Student ab;
            std::string str;

            std::getline(file, str);
            ab.set_name(str);

            std::getline(file, str);
            ab.set_speciality(str);

            int buf;
            file >> buf;
            ab.set_group(buf);

            file >> str;
            ab.set_form(str);

            int m1, m2, m3;
            file >> m1 >> m2 >> m3;
            ab.set_marks(m1, m2, m3);

            std::string kostyl;
            std::getline(file, kostyl);

            students.push_back(ab);
        }
        file.close();

        for (const auto& var : students) {
            ui->listWidget->addItem(QString::fromStdString(var.get_name()));
        }
        if (fileName.length()) {
            ui->lineEdit->setText(fileName);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
            ui->pushButton_add->setEnabled(true);
            ui->pushButton_clear->setEnabled(true);
            ui->pushButton_showInformation->setEnabled(true);
            ui->pushButton_paid->setEnabled(true);
        }
        else {
            ui->lineEdit->setText("Файл не выбран");
            ui->pushButton_2->setEnabled(false);
            ui->pushButton->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            ui->pushButton_add->setEnabled(false);
            ui->pushButton_change->setEnabled(false);
            ui->pushButton_clear->setEnabled(false);
            ui->pushButton_showInformation->setEnabled(false);
            ui->pushButton_delete->setEnabled(false);
            ui->pushButton_paid->setEnabled(false);
        }
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Выбранный файл не поддерживается");
        ui->lineEdit->setText("Файл не выбран");
        ui->pushButton_2->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_add->setEnabled(false);
        ui->pushButton_change->setEnabled(false);
        ui->pushButton_clear->setEnabled(false);
        ui->pushButton_showInformation->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_paid->setEnabled(false);
    }
}

vector<Student> ExelentPaidStudents() {
    vector<Student> list;

    for (auto& var : students) {
        if (var.get_form() == "платное") {
            if ((var.get_mark1() == 10 || var.get_mark1() == 9) && (var.get_mark2() == 10 || var.get_mark2() == 9) && (var.get_mark3() == 10 || var.get_mark3() == 9)) {
                list.push_back(var);
            }
        }
    }

    return list;
}

bool IsGroupViewed(vector<Student> a, int ind) {
    for (int i = 0; i < ind; ++i) {
        if (a[i].get_group() == a[ind].get_group()) {
            return true;
        }
    }
    return false;
}

bool compName(const Student& obj1, const Student& obj2) {
    std::string str1 = obj1.get_name();
    std::string str2 = obj2.get_name();
    for (int i = 0; i < str1.size() && i < str2.size(); ++i) {
        if (tolower(str1[i]) < tolower(str2[i])) return true;
        if (tolower(str1[i]) > tolower(str2[i])) return false;
    }
    return false;
}


vector<vector<Student>> SortedGroups() {
    vector<vector<Student>> groups;
    int size = 0;
    for (int i = 0; i < students.size(); ++i) {
        if (!IsGroupViewed(students, i)) {
            size++;
            vector<Student> abob;
            for (int j = i; j < students.size(); ++j) {
                if (students[i].get_group() == students[j].get_group()) {
                    abob.push_back(students[j]);
                }
            }
            groups.push_back(abob);
        }
    }

    for (int i = 0; i < groups.size(); ++i) {
        std::sort(groups[i].begin(), groups[i].end(), compName);
    }

    return groups;
}


bool compAverage(const Student& obj1, const Student& obj2) {
    return (obj1.get_average() > obj2.get_average());
}


vector<Student> BudgetSorted() {
    vector<Student> budget;
    for (auto& var : students) {
        if (var.get_form() == "бюджет") {
            budget.push_back(var);
        }
    }
    std::sort(budget.begin(), budget.end(), compAverage);
    return budget;
}


vector<Student> PaidSorted() {
    vector<Student> paid;
    for (auto& var : students) {
        if (var.get_form() == "платное") {
            paid.push_back(var);
        }
    }
    std::sort(paid.begin(), paid.end(), compAverage);
    return paid;
}

bool eqName(std::string str1, std::string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), tolower);
    transform(str2.begin(), str2.end(), str2.begin(), tolower);
    if (str1.find(str2, 0) != std::string::npos)
        return true;
    else
        return false;
}

std::string findName;

vector<Student> FindName() {
    vector<Student> finded;
    for (const auto& var : students) {
        if (eqName(var.get_name(), findName)) {
            finded.push_back(var);
        }
    }
    return finded;
}

std::string findGroup;

vector<Student> FindGroup() {
    vector<Student> group;
    for (auto& var : students) {
        if (var.get_group().toStdString() == findGroup) {
            group.push_back(var);
        }
    }
    return group;
}

std::string findForm;

vector<Student> FindForm() {
    vector<Student> form;
    for (auto& var : students) {
        if (var.get_form().toStdString() == findForm) {
            form.push_back(var);
        }
    }
    return form;
}


vector<Student> ToLine(vector<vector<Student>> a) {
    vector<Student> newVec;
    for (auto& var : a) {
        for (auto& st : var) {
            newVec.push_back(st);
        }
    }
    return newVec;
}


void Show(const vector<Student>& stud) {
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о студентах");
    window->setGeometry(QRect(350, 150, 800, 250));
    window->resize(900, 500);
    QTableWidget *tableWidget = new QTableWidget();

    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(8);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Специальность");
            headers1.append("Группа");
            headers1.append("Форма обучения");
            headers1.append("ОАиП");
            headers1.append("Математика");
            headers1.append("Философия");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < stud.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(stud[i].get_name())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(stud[i].get_speciality())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(stud[i].get_group()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(stud[i].get_form()));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(stud[i].get_mark1())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(stud[i].get_mark2())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(stud[i].get_mark3())));
        tableWidget->setItem(i, 7, new QTableWidgetItem(stud[i].get_average()));
        tableWidget->resizeColumnsToContents();
    }
    window->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    vector<Student> st = ExelentPaidStudents();
    if (st.size())
        Show(st);
    else
        QMessageBox::information(this, "Пусто", "Такие студенты отсутствуют");
}


void MainWindow::on_pushButton_clicked()
{
    students = ToLine(SortedGroups());
    std::fstream file;
    file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
    for (int i = 0; i < students.size(); ++i) {
        file << students[i].get_name() << "\n";
        file << students[i].get_speciality() << "\n";
        file << students[i].get_group().toStdString() << "\n";
        file << students[i].get_form().toStdString() << "\n";
        file << students[i].get_mark1() << " " << students[i].get_mark2() << " " << students[i].get_mark3();
        if (i != students.size() - 1)
            file << "\n";
    }
    file.close();
    ui->listWidget->clear();
    for (const auto& var : students) {
        ui->listWidget->addItem(QString::fromStdString(var.get_name()));
    }
}


void MainWindow::on_pushButton_paid_clicked()
{
    vector<Student> paid = PaidSorted();
    vector<Student> budget = BudgetSorted();

    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о студентах");
    window->setGeometry(QRect(350, 150, 800, 250));
    window->resize(900, 500);
    QTableWidget *tableWidget = new QTableWidget();

    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(8);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Специальность");
            headers1.append("Группа");
            headers1.append("Форма обучения");
            headers1.append("ОАиП");
            headers1.append("Математика");
            headers1.append("Философия");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < paid.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(paid[i].get_name())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(paid[i].get_speciality())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(paid[i].get_group()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(paid[i].get_form()));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(paid[i].get_mark1())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(paid[i].get_mark2())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(paid[i].get_mark3())));
        tableWidget->setItem(i, 7, new QTableWidgetItem(paid[i].get_average()));
        tableWidget->resizeColumnsToContents();
    }

    QTableWidget *tableWidget2 = new QTableWidget();
    layout->addWidget(tableWidget2, 1, 0);

    tableWidget2->setColumnCount(8);
    tableWidget2->setShowGrid(true);
    tableWidget2->setHorizontalHeaderLabels(headers1);

    tableWidget2->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget2->horizontalHeader()->setStretchLastSection(true);
    tableWidget2->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < budget.size(); ++i) {
        tableWidget2->insertRow(i);
        tableWidget2->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(budget[i].get_name())));
        tableWidget2->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(budget[i].get_speciality())));
        tableWidget2->setItem(i, 2, new QTableWidgetItem(budget[i].get_group()));
        tableWidget2->setItem(i, 3, new QTableWidgetItem(budget[i].get_form()));
        tableWidget2->setItem(i, 4, new QTableWidgetItem(QString::number(budget[i].get_mark1())));
        tableWidget2->setItem(i, 5, new QTableWidgetItem(QString::number(budget[i].get_mark2())));
        tableWidget2->setItem(i, 6, new QTableWidgetItem(QString::number(budget[i].get_mark3())));
        tableWidget2->setItem(i, 7, new QTableWidgetItem(budget[i].get_average()));
        tableWidget2->resizeColumnsToContents();
    }
    window->show();
}

bool checked = false;

void MainWindow::on_pushButton_3_clicked()
{
    Dialog *win = new Dialog("name");
    win->show();
    win->exec();

    ui->listWidget->clear();
    for (const auto& var : students) {
        ui->listWidget->addItem(QString::fromStdString(var.get_name()));
    }

    try {
        vector<Student> finded = FindName();
        if (checked) {
            if (finded.size()) {
                ui->listWidget->clear();
                for (const auto& var : finded) {
                    ui->listWidget->addItem(QString::fromStdString(var.get_name()));
                }
            }
            else {
                QMessageBox::critical(this, "Ошибка", "Такого студента не найдено");
            }
        }
        checked = false;
    }
    catch (...) {
        //QMessageBox::critical(this, "Ошибка", "Такого студента не найдено");
    }
}


void CheckGroup(const std::string& group) {
    for (auto& var : group) {
        if (!isdigit(var)) {
            throw "Invalid group number";
        }
    }
}


void CheckForm(const std::string& form) {
    if (form != "платное" && form != "бюджет") {
        throw "Invalid group number";
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    Dialog *win = new Dialog("group");
    win->show();
    win->exec();

    ui->listWidget->clear();
    for (const auto& var : students) {
        ui->listWidget->addItem(QString::fromStdString(var.get_name()));
    }

    try {
        vector<Student> finded = FindGroup();
        if (checked) {
            if (finded.size()) {
                ui->listWidget->clear();
                for (const auto& var : finded) {
                    ui->listWidget->addItem(QString::fromStdString(var.get_name()));
                }
            }
            else {
                QMessageBox::critical(this, "Ошибка", "Такой группы не найдено");
            }
        }
    }
    catch (...) {
        //QMessageBox::critical(this, "Ошибка", "Таких студентов не найдено");
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    Dialog *win = new Dialog("form");
    win->show();
    win->exec();

    ui->listWidget->clear();
    for (const auto& var : students) {
        ui->listWidget->addItem(QString::fromStdString(var.get_name()));
    }

    try {
        vector<Student> finded = FindForm();
        if (checked) {
            if (finded.size()) {
                ui->listWidget->clear();
                for (const auto& var : finded) {
                    ui->listWidget->addItem(QString::fromStdString(var.get_name()));
                }
            }
            else {
                QMessageBox::critical(this, "Ошибка", "Студентов такой формы не найдено");
            }
        }
    }
    catch (...) {
        //QMessageBox::critical(this, "Ошибка", "Таких студентов не найдено");
    }
}


void Dialog::on_pushButton_clicked()
{
    findName = ui->lineEdit->text().toStdString();
    findGroup = ui->lineEdit->text().toStdString();
    findForm = ui->lineEdit->text().toStdString();

    if (instr == "name") {
        window()->close();
    }
    else if (instr == "group") {
        try {
            CheckGroup(findGroup);
            window()->close();
        }
        catch (...) {
            ui->lineEdit->clear();
            QMessageBox::critical(this, "Ошибка", "Некорректный номер группы");
        }
    }
    else if (instr == "form") {
        try {
            CheckForm(findForm);
            window()->close();
        }
        catch (...) {
            ui->lineEdit->clear();
            QMessageBox::critical(this, "Ошибка", "Некорректная форма обучения");
        }
    }
    checked = true;
}


Student newStudent;
bool error = true;

void MainWindow::on_pushButton_add_clicked()
{
    NewStudent *win = new NewStudent(this);
    win->show();
    win->exec();

    if (!error) {
        std::fstream file;
        file.open(fileName.toStdString(), std::ios::out | std::ios::app);
        file << "\n" << newStudent.get_name() << "\n";
        file << newStudent.get_speciality() << "\n";
        file << newStudent.get_group().toStdString() << "\n";
        file << newStudent.get_form().toStdString() << "\n";
        file << newStudent.get_mark1() << " " << newStudent.get_mark2() << " " << newStudent.get_mark3();
        file.close();

        students.push_back(newStudent);
        ui->listWidget->clear();
        for (const auto& var : students) {
            ui->listWidget->addItem(QString::fromStdString(var.get_name()));
        }
    }
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


void NewStudent::on_pushButton_clicked()
{
    QString newName = ui->lineEdit_name->text();
    QString newSpec = ui->lineEdit_speciality->text();
    QString newGroup = ui->lineEdit_group->text();
    QString newForm = ui->lineEdit_form->text();

    try {
        int newMark1 = ui->lineEdit_mark1->text().toInt();
        int newMark2 = ui->lineEdit_mark2->text().toInt();
        int newMark3 = ui->lineEdit_mark3->text().toInt();
        CheckGroup(newGroup.toStdString());
        CheckForm(newForm.toStdString());
        newStudent.set_name(newName.toStdString());
        newStudent.set_speciality(newSpec.toStdString());
        newStudent.set_group(newGroup.toInt());
        newStudent.set_form(newForm.toStdString());
        newStudent.set_marks(newMark1, newMark2, newMark3);
        error = false;
        window()->close();
    }
    catch (...) {
        error = true;
        QMessageBox::critical(this, "Ошибка", "Ошибка ввода");
    }
}


void MainWindow::on_pushButton_delete_clicked()
{
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].get_name() == ui->listWidget->currentItem()->text().toStdString()) {
            students.erase(i);
        }
    }
    std::fstream file;
    file.open(fileName.toStdString(), std::ios::trunc | std::ios::out);
    for (int i = 0; i < students.size(); ++i) {
        file << students[i].get_name() << "\n";
        file << students[i].get_speciality() << "\n";
        file << students[i].get_group().toStdString() << "\n";
        file << students[i].get_form().toStdString() << "\n";
        file << students[i].get_mark1() << " " << students[i].get_mark2() << " " << students[i].get_mark3();
        if (i != students.size() - 1)
            file << "\n";
    }
    file.close();
    ui->listWidget->clear();
    for (const auto& var : students) {
        ui->listWidget->addItem(QString::fromStdString(var.get_name()));
    }
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}


void MainWindow::on_pushButton_showInformation_clicked()
{
    vector<Student> st;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        for (int j = 0; j < students.size(); ++j) {
            if (students[j].get_name() == ui->listWidget->item(i)->text().toStdString()) {
                st.push_back(students[j]);
            }
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о студентах");
    window->setGeometry(QRect(350, 150, 800, 250));
    window->resize(900, 350);
    QTableWidget *tableWidget = new QTableWidget();

    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(8);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Специальность");
            headers1.append("Группа");
            headers1.append("Форма обучения");
            headers1.append("ОАиП");
            headers1.append("Математика");
            headers1.append("Философия");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < st.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(st[i].get_name())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(st[i].get_speciality())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(st[i].get_group()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(st[i].get_form()));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(st[i].get_mark1())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(st[i].get_mark2())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(st[i].get_mark3())));
        tableWidget->setItem(i, 7, new QTableWidgetItem(st[i].get_average()));
        tableWidget->resizeColumnsToContents();
    }
    window->show();
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->listWidget->clear();
    for (const auto& var : students) {
        ui->listWidget->addItem(QString::fromStdString(var.get_name()));
    }
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
    ui->listWidget->clearSelection();

    if (rand() % 25 == 1) {
        QPixmap pix("C:/Users/user/Pictures/qt.jpg");
        QLabel *image = new QLabel();
        image->setPixmap(pix.scaled(780, 328));
        image->resize(780, 328);
        image->show();
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    vector<Student> st;
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].get_name() == ui->listWidget->currentItem()->text().toStdString()) {
            st.push_back(students[i]);
        }
    }
    QWidget *window = new QWidget();
    window->setWindowTitle("Информация о студенте");
    window->setGeometry(QRect(350, 350, 800, 250));
    window->resize(900, 10);
    QTableWidget *tableWidget = new QTableWidget();

    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(tableWidget, 0, 0);

    tableWidget->setColumnCount(8);
    tableWidget->setShowGrid(true);

    QStringList headers1;
            headers1.append("ФИО");
            headers1.append("Специальность");
            headers1.append("Группа");
            headers1.append("Форма обучения");
            headers1.append("ОАиП");
            headers1.append("Математика");
            headers1.append("Философия");
            headers1.append("Средний балл");
    tableWidget->setHorizontalHeaderLabels(headers1);

    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < st.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(st[i].get_name())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(st[i].get_speciality())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(st[i].get_group()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(st[i].get_form()));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(st[i].get_mark1())));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(st[i].get_mark2())));
        tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(st[i].get_mark3())));
        tableWidget->setItem(i, 7, new QTableWidgetItem(st[i].get_average()));
        tableWidget->resizeColumnsToContents();
    }
    window->show();
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_change->setEnabled(true);
    ui->pushButton_delete->setEnabled(true);
}

void ChangeStudent(int i) {
    NewStudent *win = new NewStudent(students[i]);
    win->setModal(true);
    win->exec();

    if (!error) {
        students[i] = newStudent;
        std::fstream file;
        file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
        for (int i = 0; i < students.size(); ++i) {
            file << students[i].get_name() << "\n";
            file << students[i].get_speciality() << "\n";
            file << students[i].get_group().toStdString() << "\n";
            file << students[i].get_form().toStdString() << "\n";
            file << students[i].get_mark1() << " " << students[i].get_mark2() << " " << students[i].get_mark3();
            if (i != students.size() - 1)
                file << "\n";
        }
        file.close();
    }
}

void MainWindow::on_pushButton_change_clicked()
{
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].get_name() == ui->listWidget->currentItem()->text().toStdString()) {
            ChangeStudent(i);
            ui->listWidget->clear();
            for (const auto& var : students) {
                ui->listWidget->addItem(QString::fromStdString(var.get_name()));
            }
            break;
        }
    }
    ui->pushButton_change->setEnabled(false);
    ui->pushButton_delete->setEnabled(false);
}

