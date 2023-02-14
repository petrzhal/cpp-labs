#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

enum SearchOpenConfig {
    height,
    weight,
    number,
    age
};

namespace Ui {
class search;
}

class search : public QDialog
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    explicit search(SearchOpenConfig);
    ~search();

private slots:
    void on_pushButton_clicked();

private:
    Ui::search *ui;
};

#endif // SEARCH_H
