#ifndef SONG_H
#define SONG_H
#include <QString>
#include <QUrl>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
#include <exceptions.h>

class Song
{
private:
    QString m_song_name;
    QString m_author;
    QString m_album;
    size_t m_year;
    QString m_genre;
    QUrl m_url;
    size_t m_duration;
    QString m_codec;

    QStringList m_listnames;

public:
    Song(const QString &songName, const QString &author, const QString &album,
         size_t year, const QString &genre, const QString &url, size_t duration,
         const QString &codec);

    Song(const Song &another);
    //get functions
    QString getSongName() const;
    QString getAuthor() const;
    QString getAlbum() const;
    size_t getYear() const;
    QString getGenre() const;
    QString getUrl() const; // 'f' - url with file, 'd' - only directory
    size_t getDuration() const;
    QString getCodec() const;
    QString getFileName() const;

    QStringList& getListNames();

    //set functions
    //void setSongName(const QString &name);

    void setAuthor(const QString &name);
    void setAlbum(const QString &name);
    void setYear(size_t year);
    void setGenre(const QString &genre);
    //void setUrl(const QString &url);
    //void setDuration(size_t duration);
    void setCodec(const QString &codec);
    void setListNames(const QStringList &list);
    void save() const;
    //compare functions

    bool compareAuthorGreater(const Song &another) const;
    bool compareUrlGreater(const Song &another) const;

    bool operator<(const Song &another) const;
    bool operator>(const Song &another) const;
    bool operator==(const Song &another) const;
    ~Song();

};

#endif // SONG_H
