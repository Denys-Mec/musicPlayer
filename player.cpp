#include "player.h"

Player::Player()
{

}

void Player::addSong(const QString &songName, const QString &author, const QString &album,
             size_t year, const QString &genre, const QString &url, size_t duration,
             const QString &codec)
{
    Song song(songName, author, album, year, genre, url, duration, codec);
    m_list.append(song);
}

void Player::addSong(const QString &file)
{
    TagLib::FileRef f(file.toLocal8Bit().data());

    TagLib::Tag *tag = f.tag();
    if(tag)
    {
        QAudioDecoder decoder;
        decoder.setSourceFilename(file);

        this->addSong(QUrl(file).fileName(), tag->artist().toCString(),
                                tag->album().toCString(), tag->year(),
                                tag->genre().toCString(), file, f.audioProperties()->length(),
                                decoder.audioFormat().codec());
    }
    else
        throw ErrorReadingMediaData(file);
}


QList<Song>::iterator Player::searchSong(const QString &fileName)
{

    for(auto iter {m_list.begin()}; iter != m_list.end(); iter++)
    {
        if(iter->getFileName() == fileName)
            return iter;
    }
    return m_list.end();
}

void Player::deleteSong(Player::iterator iter)
{
    if(iter != m_list.end())
        m_list.erase(iter);

}

QList<Song>::iterator Player::begin() const
{
    return const_cast<Player*>(this)->m_list.begin();
}
QList<Song>::iterator Player::end() const
{
    return const_cast<Player*>(this)->m_list.end();
}
QList<Song>::const_iterator Player::cbegin() const
{
    return m_list.cbegin();
}
QList<Song>::const_iterator Player::cend() const
{
    return m_list.cend();
}

int Player::size() const
{
    return m_list.size();
}

void mySort(Player::iterator first, Player::iterator last)
{
    typedef  Player::iterator iter;
    QVector<iter> array;

    for(auto elem {first}; elem != last; ++elem){
        array.append(elem);
    }
    for (int k = array.size()/2; k >= 1; k /= 2)
            for (int i = k; i < array.size(); i++)
                for (int j = i; j >= k && *array[j-k] > *array[j]; j -= k)
                {
                    Song temp {*array[j]};
                    *array[j] = *array[j-k];
                    *array[j-k] = temp;
                }
}

void Player::sort()
{
    //qSort(m_list.begin(), m_list.end());
    mySort(m_list.begin(), m_list.end());
}
void Player::reverse()
{
    qSort(m_list.begin(), m_list.end(), [](const Song &num1, const Song &num2){
        return !(num1<num2);
    });
}
void Player::sortByCodec()
{
    qSort(m_list.begin(), m_list.end(), [](const Song &num1, const Song &num2){
        if(num1.getCodec() == num2.getCodec())
            return num1.getYear() > num2.getYear();
        return num1.getCodec() < num2.getCodec();
    });
}
void Player::sortByGenre()
{
    qSort(m_list.begin(), m_list.end(), [](const Song &num1, const Song &num2){
        if(num1.getGenre() == num2.getGenre())
            return num1.getDuration() > num2.getDuration();
        if(num1.getGenre() == "" && num2.getGenre() != "")
            return false;
        if(num2.getGenre() == "" && num1.getGenre() != "")
            return true;
        return num1.getGenre() < num2.getGenre();
    });
}

Player::iterator Player::find(const QString &fileName)
{
    for(auto iter{m_list.begin()}; iter != m_list.end(); ++iter)
    {
        if(iter->getFileName() == fileName)
            return iter;
    }
    return m_list.end();
}

QStringList Player::getAlbumNames() const
{
    QStringList list;
    for(auto iter{m_list.cbegin()}; iter != m_list.cend(); ++iter)
    {
        auto elem {list.begin()};
        for(; elem != list.end(); ++elem)
        {
            if(*elem == iter->getAlbum())
                break;
        }
        if(elem == list.end() && iter->getAlbum() != "")
        {
            list.push_back(iter->getAlbum());
        }
    }
    return list;
}
QStringList Player::getAuthorNames() const
{
    QStringList list;
    for(auto iter{m_list.cbegin()}; iter != m_list.cend(); ++iter)
    {
        auto elem {list.begin()};
        for(; elem != list.end(); ++elem)
        {
            if(*elem == iter->getAuthor())
                break;
        }
        if(elem == list.end() && iter->getAuthor() != "")
        {
            list.push_back(iter->getAuthor());
        }
    }
    return list;
}
QStringList Player::getGenreNames() const
{
    QStringList list;
    for(auto iter{m_list.cbegin()}; iter != m_list.cend(); ++iter)
    {
        auto elem {list.begin()};
        for(; elem != list.end(); ++elem)
        {
            if(*elem == iter->getGenre())
                break;
        }
        if(elem == list.end() && iter->getGenre() != "")
        {
            list.push_back(iter->getGenre());
        }
    }
    return list;
}

Player::playlist Player::getAlbumPlaylist(const QString &name) const
{
    playlist list;
    for(auto iter{m_list.begin()}; iter != m_list.end(); ++iter)
    {
        if(iter->getAlbum() == name)
            list.push_back(*iter);
    }
    return list;
}
Player::playlist Player::getAuthorPlaylist(const QString &name) const
{
    playlist list;
    for(auto iter{m_list.begin()}; iter != m_list.end(); ++iter)
    {
        if(iter->getAuthor() == name)
            list.push_back(*iter);
    }
    return list;
}
Player::playlist Player::getGenrePlaylist(const QString &name) const
{
    playlist list;
    for(auto iter{m_list.begin()}; iter != m_list.end(); ++iter)
    {
        if(iter->getGenre() == name)
            list.push_back(*iter);
    }
    return list;
}

void Player::addSongToPlaylist(iterator iter, const QString &playlist)
{
    iter->getListNames().push_back(playlist);
}
void Player::deleteSongFromPlaylist(iterator iter, const QString &playlist)
{
    iter->getListNames().removeAll(playlist);
}
Player::playlist Player::getPlaylist(const QString &playlistName)
{
    playlist list;
    for(auto iter{m_list.begin()}; iter != m_list.end(); ++iter)
    {
        if(iter->getListNames().contains(playlistName))
            list.push_back(*iter);
    }
    return list;
}
void Player::clear()
{
    m_list.clear();

}

void operator>>(const Player &player, QFile &file)
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw ErrorOpeningDataFile(file.fileName());


    QTextStream out(&file);
    for(auto iter{player.begin()}; iter != player.end(); ++iter)
    {
        out << iter->getUrl() << Qt::endl;
    }
    file.close();

}

void operator<<(Player &player, QFile &file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw ErrorOpeningDataFile(file.fileName());


    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        player.addSong(line);
    }
    file.close();
}

Player::~Player()
{
    clear();
}


