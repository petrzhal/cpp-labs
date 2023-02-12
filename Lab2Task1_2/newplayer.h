#ifndef NEWPLAYER_H
#define NEWPLAYER_H

#include <QDialog>

enum FormCreationConfig {
    Add,
    Change
};

namespace Ui {
class NewPlayer;
}

class NewPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit NewPlayer(QWidget *parent = nullptr);
    explicit NewPlayer(FormCreationConfig);
    ~NewPlayer();

private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::NewPlayer *ui;
};

#endif // NEWPLAYER_H
