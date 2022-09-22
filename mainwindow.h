#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include <QDir>
#include <QFile>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QMediaPlaylist>
#include <QToolTip>
#include <QUrl>
#include <QFileDialog>
#include <stdlib.h>
#include <QStandardItemModel>
#include <QSlider>
//#include <QAudioDecoder>
#include <QMap>
//#include <taglib/fileref.h>
//#include <taglib/tag.h>
//#include <taglib/tpropertymap.h>

#include "player.h"

#include "dialog.h"

#define DATA_FILE "data"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Player::iterator iter;
private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();
    void loadFiles(QStringList list);
    void loadTable();
    void loadTable(const Player::playlist &list);
    void loadPlayList();

    void on_pushButton_8_clicked();

    void on_tableWidget_cellEntered(int row, int column);
    void sortFiles();

    void on_pushButton_9_clicked();

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_lineEdit_textEdited(const QString &arg1);

    void addTableItem(const Song &song, const int line);
    // duration_parameter, year_parameter:
    // 0 - все до даного значення, 1 - все після даного значення, 2 - тільки з заданим значенням
    // search_type: 't' - title, 'a' - author, 'c' - codec
    void find(const QString &name, size_t duration = 0, size_t year = 0, const int duration_parameter = 1,
              const int year_parameter = 1, const char search_type = 't');

    void on_pushButton_13_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_label_linkHovered(const QString &link);

    void on_pushButton_10_clicked();


private:
    QStringList m_playlist;

    int m_sort_type;
    Player m_full_playlist;

    QStandardItemModel  *m_mediaPlayListModel;   // Модель данных плейлиста для отображения
    QMediaPlayer        *m_mediaPlayer;          // Проигрыватель треков
    QMediaPlaylist      *m_mediaPlaylist;        // Плейлиста проигрывателя
    Player::playlist m_mediaList;
    bool m_play;
    QFile *data;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
