#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMetaDataReaderControl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    data = new QFile(DATA_FILE);

    ui->pushButton_4->hide();

    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //hide search buttons
    ui->lineEdit->hide();
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->frame_9->hide();
    ui->horizontalSpacer_3->changeSize(12, 20, QSizePolicy::Expanding);
    ui->tableWidget->horizontalHeader()->show();
    m_sort_type = 0;
    ui->listWidget_2->hide();
    ui->frame_10->hide();


    m_mediaPlayListModel = new QStandardItemModel(this);

    m_play = false;
    m_mediaPlayer = new QMediaPlayer(this);          // Инициализируем плеер
    m_mediaPlaylist = new QMediaPlaylist(m_mediaPlayer);  // Инициализируем плейлист
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);          // Устанавливаем плейлист в плеер
    m_mediaPlayer->setVolume(70);                    // Устанавливаем громкость воспроизведения треков
    m_mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);  // Устанавливаем циклический режим проигрывания плейлиста

    connect(m_mediaPlaylist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->label->setText(m_mediaList[index].getFileName());
    });
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, ui->horizontalSlider, &QSlider::setMaximum);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::sliderMoved, m_mediaPlayer, &QMediaPlayer::setPosition);

    try{
        m_full_playlist << *data;
    }
    catch(Error e)
    {
        QMessageBox::warning(this, "", e.data());
    }

    loadTable();
}



MainWindow::~MainWindow()
{
    delete m_mediaPlayListModel;   // Модель данных плейлиста для отображения
    delete m_mediaPlayer;          // Проигрыватель треков
    delete m_mediaPlaylist;
    delete ui;
}


void MainWindow::on_pushButton_6_clicked()
{
    if(ui->frame_2->isHidden()){
        ui->frame_2->show();
    }else{
        ui->frame_2->hide();
    }

}


void MainWindow::on_pushButton_7_clicked()
{
    if(!ui->frame_10->isHidden())
    {
        on_listWidget_itemClicked(ui->listWidget->currentItem());
    }
    if(ui->lineEdit->isHidden()){
        ui->horizontalSpacer_3->changeSize(12, 20, QSizePolicy::Fixed, QSizePolicy::Expanding);
        ui->lineEdit->show();
        ui->pushButton_10->show();
        ui->pushButton_9->show();


    }else{
        ui->lineEdit->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->horizontalSpacer_3->changeSize(12, 20, QSizePolicy::Expanding);
        ui->frame_9->hide();
    }
}

void MainWindow::sortFiles()
{
    ui->tableWidget->sortByColumn(-1);
    switch (m_sort_type) {
    case 0:
        m_full_playlist.sort();
        break;
    case 1:
        m_full_playlist.reverse();
        break;
    case 2:
        m_full_playlist.sortByCodec();
        break;
    case 3:
        m_full_playlist.sortByGenre();
        break;
    }
}

void MainWindow::loadFiles(QStringList list)
{
    for(auto e : list){

        try {
            m_full_playlist.addSong(e);
        }  catch (Error e) {
            QMessageBox::warning(this, "", e.data());
        }

    }
    sortFiles();
    try{
        m_full_playlist >> *data;
    }
    catch(Error e)
    {
        QMessageBox::warning(this, "", e.data());
    }
}

void MainWindow::loadTable()
{
    int n  {0};
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(m_full_playlist.size());
    for(auto iter {m_full_playlist.cbegin()}; iter != m_full_playlist.cend(); ++iter){
        addTableItem(*iter, n);
        n++;
    }
}

void MainWindow::loadPlayList()
{
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(m_playlist);
}
void MainWindow::on_pushButton_11_clicked()
{
    switch(ui->listWidget->currentRow()){
    case 1:
        if(!ui->tableWidget->isHidden())
        {
            Dialog dialog(ui->listWidget_2->currentItem()->text(), m_full_playlist);

            dialog.exec();
            loadTable(m_full_playlist.getPlaylist(ui->listWidget_2->currentItem()->text()));

        }else
        {
            if(!ui->frame_10->isHidden())
            {
                ui->pushButton_11->setText("Добавити");
                ui->pushButton_12->setText("Видалити");
                if(!m_playlist.contains(ui->lineEdit_2->text()))
                {
                    for(auto iter{m_full_playlist.begin()}; iter != m_full_playlist.end();++iter)
                    {
                        if(iter->getListNames().contains(ui->label_2->text()))
                        {
                            QStringList newlist {iter->getListNames()};
                            newlist.removeOne(ui->label_2->text());
                            newlist.push_back(ui->lineEdit_2->text());
                            iter->setListNames(newlist);
                        }
                    }
                    m_playlist.push_back(ui->lineEdit_2->text());
                    m_playlist.removeOne(ui->label_2->text());
                }
                on_listWidget_itemClicked(ui->listWidget->currentItem());
            }else{
                m_playlist.push_back("Playlist " + QString::number(m_playlist.size()));

            }
            loadPlayList();
        }


        break;
    case 3:
        if(!ui->frame_10->isHidden()){
            auto item {m_full_playlist.find(ui->label_2->text())};
            item->setAuthor(ui->lineEdit_2->text());
            item->setAlbum(ui->lineEdit_3->text());
            item->setYear(ui->spinBox_2->value());
            item->setCodec(ui->lineEdit_4->text());
            item->setGenre(ui->lineEdit_5->text());
            try {
                item->save();
            }  catch (Error e) {
                QMessageBox::warning(this, "", e.data());
            }

            ui->frame_10->hide();

        }else{
            QFileDialog dialog(this);
            dialog.setFileMode(QFileDialog::ExistingFiles);
            dialog.exec();
            QStringList selectedFiles = dialog.selectedFiles();
            if(!selectedFiles.isEmpty()){
                loadFiles(selectedFiles);

            }
        }
        loadTable();
        on_listWidget_itemClicked(ui->listWidget->currentItem());
        break;
    }




}

void MainWindow::on_pushButton_12_clicked()
{
    QList<QTableWidgetItem*> item = ui->tableWidget->selectedItems();
 if(!ui->frame_10->isHidden())
    {
        ui->frame_10->hide();
        ui->pushButton_11->setText("Добавити");
        ui->pushButton_12->setText("Видалити");
        on_listWidget_itemClicked(ui->listWidget->currentItem());
    }else{
        switch (ui->listWidget->currentRow()) {
        case 1:
        {
            if(ui->tableWidget->isHidden())
            {
                for(auto iter{m_full_playlist.begin()}; iter != m_full_playlist.end(); ++iter)
                {
                    if(iter->getListNames().contains(ui->listWidget_2->currentItem()->text()))
                    {
                        m_full_playlist.deleteSongFromPlaylist(iter, ui->listWidget_2->currentItem()->text());
                    }
                }

                m_playlist.removeOne(ui->listWidget_2->currentItem()->text());
                loadPlayList();
            }else{
                if(ui->tableWidget->currentRow()>=0){
                    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

                    for(int i{0}; i<items.size(); i += 7)
                    {

                        auto song {m_full_playlist.find(items[i]->text())};
                        m_full_playlist.deleteSong(song);
                        try{
                            m_full_playlist >> *data;
                        }
                        catch(Error e)
                        {
                            QMessageBox::warning(this, "", e.data());
                        }
                    }

                    loadTable();
                }
            }
            }
            break;
        case 3:
            if(ui->tableWidget->currentRow()>=0){
                QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

                for(int i{0}; i<items.size(); i += 7)
                {

                    auto song {m_full_playlist.find(items[i]->text())};
                    m_full_playlist.deleteSong(song);
                    try{
                        m_full_playlist >> *data;
                    }
                    catch(Error e)
                    {
                        QMessageBox::warning(this, "", e.data());
                    }
                }

                loadTable();
            }
            break;
        }


    }


}


void MainWindow::on_pushButton_8_clicked()
{   
    if(ui->tableWidget->rowCount() > 1){

        sortFiles();
        switch (m_sort_type) {
        case 0:
            ui->pushButton_8->setToolTip("Звичайне сортування");
        break;
        case 1:
            ui->pushButton_8->setToolTip("Зворотнє сортування");
        break;
        case 2:
            ui->pushButton_8->setToolTip("Сортування по кодеку та року випуску");
        break;
        case 3:
            ui->pushButton_8->setToolTip("Сортування по жанру та тривалості виконання");
            m_sort_type = -1;
        break;
        }
        m_sort_type++;
        loadTable();
    }
}


void MainWindow::on_tableWidget_cellEntered(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    if (item == NULL) {
        return;
    }
    QToolTip::showText(QCursor::pos(), item->text());
}


void MainWindow::on_pushButton_9_clicked()
{
    if(ui->frame_9->isHidden()){
        ui->frame_9->show();
    }else{
        ui->frame_9->hide();
    }
}

void MainWindow::addTableItem(const Song &song, const int line)
{
    QTableWidgetItem *item;
    item = new QTableWidgetItem;
    item->setText(song.getFileName());
    ui->tableWidget->setItem(line, 0, item);

    item = new QTableWidgetItem;
    item->setText(song.getAuthor());
    ui->tableWidget->setItem(line, 1, item);

    item = new QTableWidgetItem;
    item->setText(song.getAlbum());
    ui->tableWidget->setItem(line, 2, item);

    item = new QTableWidgetItem;
    item->setText(QString::number(song.getYear()));
    ui->tableWidget->setItem(line, 3, item);

    item = new QTableWidgetItem;
    item->setText(song.getGenre());
    ui->tableWidget->setItem(line, 4, item);

    int seconds = song.getDuration() % 60;
    int minutes = (song.getDuration() - seconds) / 60;
    item = new QTableWidgetItem;
    item->setText(QString::number(minutes) + ":" + QString::number(seconds));
    ui->tableWidget->setItem(line, 5, item);

    item = new QTableWidgetItem;
    item->setText(song.getCodec());
    ui->tableWidget->setItem(line, 6, item);

}

void MainWindow::loadTable(const Player::playlist &list)
{
    int n  {0};
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(list.size());


    for(auto iter{list.begin()}; iter != list.end(); ++iter)
    {
        addTableItem(*iter, n);
        n++;
    }
}

void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{

    switch(ui->listWidget->currentRow()){
    case 1:
        loadTable(m_full_playlist.getPlaylist(item->text()));
        break;
    case 2:
        loadTable(m_full_playlist.getAlbumPlaylist(item->text()));
        break;
    case 4:
        loadTable(m_full_playlist.getGenrePlaylist(item->text()));
        break;
    case 5:
        loadTable(m_full_playlist.getAuthorPlaylist(item->text()));
        break;

    }
    ui->listWidget_2->hide();
    ui->tableWidget->show();
}

void MainWindow::find(const QString &name, size_t duration, size_t year, const int duration_parameter,
          const int year_parameter, const char search_type)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    auto iter {m_full_playlist.cbegin()};
    for(; iter != m_full_playlist.cend(); ++iter)
    {
        auto temp {m_full_playlist.cend()};
        switch (search_type) {
        case 't':
            if(iter->getFileName().left(name.length()) == name)
            {
                temp = iter;
            }
            break;
        case 'a':
            if(iter->getAuthor().left(name.length()) == name)
            {
                temp = iter;
            }
            break;
        case 'c':
            if(iter->getCodec().left(name.length()) == name)
            {
                temp = iter;
            }
            break;
        }
        if(temp != m_full_playlist.cend())
        {
            switch(duration_parameter){
            case 0:
                if(temp->getDuration()>duration)
                    temp = m_full_playlist.cend();
                break;
            case 1:
                if(temp->getDuration()<duration)
                    temp = m_full_playlist.cend();
                break;
            case 2:
                if(temp->getDuration()!=duration)
                    temp = m_full_playlist.cend();
                break;
            }
        }

        if(temp != m_full_playlist.cend())
        {
            switch(year_parameter){
            case 0:
                if(temp->getYear()>year)
                    temp = m_full_playlist.cend();
                break;
            case 1:
                if(temp->getYear()<year)
                    temp = m_full_playlist.cend();
                break;
            case 2:
                if(temp->getYear()!=year)
                    temp = m_full_playlist.cend();
                break;
            }
        }

        if(temp != m_full_playlist.cend())
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            addTableItem(*temp, ui->tableWidget->rowCount() - 1);
        }
    }
}
void MainWindow::on_listWidget_itemClicked([[maybe_unused]] QListWidgetItem *item)
{
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();

    if(!ui->lineEdit->isHidden())
    {
        on_pushButton_7_clicked();
    }

    ui->tableWidget->hide();
    ui->listWidget_2->hide();
    ui->frame_10->hide();
    ui->pushButton_11->setText("Добавити");
    ui->pushButton_12->setText("Видалити");
    switch(ui->listWidget->currentRow()){
    case 0:
        ui->tableWidget->show();
        loadTable(m_mediaList);
        break;
    case 1:
        ui->listWidget_2->show();
        loadPlayList();
        ui->pushButton_11->show();
        ui->pushButton_12->show();
        ui->pushButton_13->show();
        //ui->listWidget_2->clear();
        break;
    case 2:
        ui->listWidget_2->show();
        ui->listWidget_2->clear();
        ui->listWidget_2->addItems(m_full_playlist.getAlbumNames());
        break;
    case 3:
        loadTable();
        ui->tableWidget->show();

        ui->pushButton_7->show();
        ui->pushButton_8->show();
        ui->pushButton_11->show();
        ui->pushButton_12->show();
        ui->pushButton_13->show();
        break;
    case 4:
        ui->listWidget_2->show();
        ui->listWidget_2->clear();
        ui->listWidget_2->addItems(m_full_playlist.getGenreNames());
        break;
    case 5:
        ui->listWidget_2->show();
        ui->listWidget_2->clear();
        ui->listWidget_2->addItems(m_full_playlist.getAuthorNames());
        break;
    }
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(!ui->lineEdit->isHidden())
    {
        if(!ui->frame_9->isHidden())
        {
            char search_type;
            switch (ui->comboBox->currentIndex()) {
            case 0:
                search_type = 't';
                break;
            case 1:
                search_type = 'a';
                break;
            case 2:
                search_type = 'c';
                break;
            }
            find(arg1, (ui->timeEdit->time().minute()*60)+ui->timeEdit->time().second(), ui->spinBox->value(), ui->comboBox_2->currentIndex()
                 , ui->comboBox_3->currentIndex(), search_type);

        }else
        {
            find(arg1);
        }
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    if(ui->frame_10->isHidden()){
        ui->pushButton_11->setText("Зберегти");
        ui->pushButton_12->setText("Скасувати");
        switch (ui->listWidget->currentRow()) {
        case 1:
        {
            if(ui->listWidget_2->currentRow() >= 0){
                ui->lineEdit_3->hide();
                ui->lineEdit_4->hide();
                ui->lineEdit_5->hide();
                ui->spinBox_2->hide();
                ui->label_3->hide();
                ui->label_5->hide();
                ui->label_6->hide();
                ui->label_7->hide();
                ui->label_8->hide();
                ui->label_9->hide();

                ui->tableWidget->hide();
                ui->listWidget_2->hide();
                ui->frame_10->show();
                ui->label_2->setText(ui->listWidget_2->currentItem()->text());
                ui->label_4->setText("Нова назва");
                ui->lineEdit_2->setText("");




            }
        }
            break;
        case 3:
        {
            if(ui->tableWidget->currentRow()>=0)
            {
                ui->lineEdit_3->show();
                ui->lineEdit_4->show();
                ui->lineEdit_5->show();
                ui->spinBox_2->show();
                ui->label_3->show();
                ui->label_5->show();
                ui->label_6->show();
                ui->label_7->show();
                ui->label_8->show();
                ui->label_9->show();
                ui->label_4->setText("Автор");
                ui->tableWidget->hide();
                ui->listWidget_2->hide();
                ui->frame_10->show();


                const int index {ui->tableWidget->currentRow()};
                QString name {ui->tableWidget->item(index, 0)->text()};

                auto item {m_full_playlist.find(name)};
                ui->label_2->setText(item->getFileName());
                ui->label_2->setToolTip(item->getFileName());
                int seconds = item->getDuration() % 60;
                int minutes = (item->getDuration() - seconds) / 60;
                ui->label_8->setText(QString::number(minutes) + ":" + QString::number(seconds));
                ui->lineEdit_2->setText(item->getAuthor());
                ui->lineEdit_3->setText(item->getAlbum());
                ui->spinBox_2->setValue(item->getYear());
                ui->lineEdit_4->setText(item->getCodec());
                ui->lineEdit_5->setText(item->getGenre());
            }

        }
            break;
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(m_play){
        m_mediaPlayer->pause();
        m_play = false;
    }else{
        m_mediaPlayer->play();
        m_play = true;
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, [[maybe_unused]] int column)
{
    m_mediaPlaylist->clear();
    m_mediaList.clear();
    for(int i {0}; i<ui->tableWidget->rowCount(); i++)
    {
        m_mediaPlaylist->addMedia(QUrl::fromLocalFile(m_full_playlist.find(ui->tableWidget->item(i, 0)->text())->getUrl()));
        m_mediaList.push_back(*m_full_playlist.find(ui->tableWidget->item(i, 0)->text()));
    }
    m_mediaPlaylist->setCurrentIndex(row);
    m_mediaPlayer->play();
    m_play = true;

}


void MainWindow::on_pushButton_clicked()
{
    m_mediaPlaylist->next();
}


void MainWindow::on_pushButton_3_clicked()
{
    m_mediaPlaylist->previous();
}


void MainWindow::on_label_linkHovered(const QString &link)
{
    ui->label->setToolTip(link);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit->clear();
    on_listWidget_itemClicked(ui->listWidget->currentItem());
}

