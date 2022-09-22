#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <player.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(const QString &listName, Player &player, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_tableWidget_cellEntered(int row, int column);

    void on_pushButton_2_clicked();

private:
    QString listName;
    Player &player;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
