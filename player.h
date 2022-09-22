#ifndef PLAYER_H
#define PLAYER_H
#include "song.h"
#include <QList>
#include <QFile>
#include <QAudioDecoder>


class Player
{
private:

    QList<Song> m_list;
    QList<Song>::iterator searchSong(const QString &fileName);

public:
    Player();
    typedef QList<Song>::iterator iterator;
    typedef QList<Song>::const_iterator const_iterator;

    typedef QList<Song> playlist ;


    void addSong(const QString &songName, const QString &author, const QString &album,
                 size_t year, const QString &genre, const QString &url, size_t duration,
                 const QString &codec);
    void addSong(const QString &file);
    void deleteSong(QList<Song>::iterator iter);

    int size() const;

    QStringList getAlbumNames() const;
    QStringList getAuthorNames() const;
    QStringList getGenreNames() const;

    iterator find(const QString &fileName);

    playlist getAlbumPlaylist(const QString &name) const;
    playlist getAuthorPlaylist(const QString &name) const;
    playlist getGenrePlaylist(const QString &name) const;

    void addSongToPlaylist(iterator iter, const QString &playlist);
    void deleteSongFromPlaylist(iterator iter, const QString &playlist);
    playlist getPlaylist(const QString &playlistName);

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    void sort();
    void reverse();
    void sortByCodec();
    void sortByGenre();
    void clear();

    friend void operator>>(const Player &player, QFile &file);
    friend void operator<<(Player &player, QFile &file);
    ~Player();
};

#endif // PLAYER_H
