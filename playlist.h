#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <song.h>
#include <QVector>

class Playlist
{
private:
    QString m_name;
    QVector<Song> m_list;
    QString img_url;
public:
    Playlist();
    Playlist(const QString &name);
    ~Playlist();

    typedef QVector<Song>::iterator iterator;
    typedef QVector<Song>::const_iterator const_iterator;
    int size() const;
    void setName(const QString &name);

    QString getName() const;

    void addSong(const Song &song);
    void deleteSong(iterator iter);

    void sort();

    iterator find(const QString &songName);
    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

};

#endif // PLAYLIST_H
