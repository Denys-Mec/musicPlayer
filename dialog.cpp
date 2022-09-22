#include "dialog.h"
#include "ui_dialog.h"
#include <QToolTip>
#include <QTableWidgetItem>
#include <QMessageBox>


Dialog::Dialog(const QString &listName, Player &player, QWidget *parent) :
    QDialog(parent), listName(listName), player(player),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->show();

    QTableWidgetItem *item;
    int n{0};
    ui->tableWidget->setRowCount(player.size());
    for(auto iter{player.begin()}; iter != player.end(); ++iter)
    {
        item = new QTableWidgetItem;
        item->setText(iter->getFileName());
        if(iter->getListNames().contains(listName))
            item->setCheckState(Qt::CheckState::Checked);
        else
            item->setCheckState(Qt::CheckState::Unchecked);
        ui->tableWidget->setItem(n, 0, item);
        item = new QTableWidgetItem;
        QString str {"К-ть(" + QString::number(iter->getListNames().size()) + "): "};
        for(auto e : iter->getListNames())
        {
            str += e + ", ";
        }
        item->setText(str);
        ui->tableWidget->setItem(n, 1, item);
        n++;
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    try {
        for(int i{0}; i<ui->tableWidget->rowCount(); ++i)
        {
            auto item {player.find(ui->tableWidget->item(i,0)->text())};
            if(item->getListNames().contains(listName) &&
                    ui->tableWidget->item(i,0)->checkState() == Qt::Unchecked)
            {
                QStringList newlist {item->getListNames()};
                newlist.removeOne(listName);
                item->setListNames(newlist);
            }else{
                if(ui->tableWidget->item(i,0)->checkState() == Qt::Checked)
                {
                    QStringList newlist {item->getListNames()};
                    newlist.push_back(listName);
                    item->setListNames(newlist);
                }
            }
        }


    }  catch (Error e) {
        QMessageBox::warning(this, "", e.data());
    }
    this->close();
}


void Dialog::on_tableWidget_cellEntered(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    if (item == NULL) {
        return;
    }
    QToolTip::showText(QCursor::pos(), item->text());
}


void Dialog::on_pushButton_2_clicked()
{
    this->close();
}

