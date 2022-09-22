#include "song.h"

char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

Song::Song(const QString &songName, const QString &author, const QString &album,
           size_t year, const QString &genre, const QString &url, size_t duration,
           const QString &codec)
    :m_song_name(songName), m_author(author), m_album(album), m_year(year),
      m_genre(genre), m_url(url), m_duration(duration), m_codec(codec)
{

}

Song::Song(const Song &another)
{
    m_song_name = another.m_song_name;
    m_author = another.m_author;
    m_album = another.m_album;
    m_year = another.m_year;
    m_genre = another.m_genre;
    m_url = another.m_url;
    m_duration = another.m_duration;
    m_codec = another.m_codec;
}

//get functions
QString Song::getSongName() const
{
    return m_song_name;
}
QString Song::getAuthor() const
{
    return m_author;
}
QString Song::getAlbum() const
{
    return m_album;
}
size_t Song::getYear() const
{
    return m_year;
}
QString Song::getGenre() const
{
    return m_genre;
}
QString Song::getFileName() const
{
    return m_url.fileName();
}
QString Song::getUrl() const
{
    return m_url.toString();
}

size_t Song::getDuration() const
{
    return m_duration;
}
QString Song::getCodec() const
{
    return m_codec;
}

QStringList& Song::getListNames()
{
    return m_listnames;
}

//set functions
//void Song::setSongName(const QString &name)
//{
//    m_song_name = name;
//}
void Song::setAuthor(const QString &name)
{
    m_author = name;
}
void Song::setAlbum(const QString &name)
{
    m_album = name;
}
void Song::setYear(size_t year)
{

    m_year = year;
}
void Song::setGenre(const QString &genre)
{

    m_genre = genre;
}
//void Song::setUrl(const QString &url)
//{
//    m_url = url;
//}
//void Song::setDuration(size_t duration)
//{
//    m_duration = duration;
//}
void Song::setCodec(const QString &codec)
{
    m_codec = codec;
}

void Song::setListNames(const QStringList &list)
{
    m_listnames.clear();
    for(auto e : list)
    {
        m_listnames.push_back(e);
    }

}

void Song::save() const
{
    TagLib::FileRef f(m_url.toString().toLocal8Bit().data());


    TagLib::Tag *tag = f.tag();

    if(!tag)
        throw ErrorReadingMediaData(m_url.toString());

    TagLib::String value;
    value = m_album.toLocal8Bit().data();
    tag->setAlbum(value);
    value = m_author.toLocal8Bit().data();
    tag->setArtist(value);
    tag->setYear(m_year);
    value = m_genre.toLocal8Bit().data();
    tag->setGenre(value);
    if(!f.file()->save())
        throw ErrorSavingMediaData(m_url.toString());
}
//compare operators
bool Song::compareAuthorGreater(const Song &another) const
{
    return m_author>another.m_author;
}
bool Song::compareUrlGreater(const Song &another) const
{
    return m_url.fileName()>another.m_url.fileName();
}

bool Song::operator<(const Song &another) const
{
    if(this->m_author == another.m_author)
        return this->m_url.fileName() < another.m_url.fileName();
    return this->m_author < another.m_author;
}
bool Song::operator>(const Song &another) const
{
    return !(*this < another);
}
bool Song::operator==(const Song &another) const
{
    //another times
    return this->m_author == another.m_author;
}

Song::~Song()
{

}






