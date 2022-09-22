#ifndef PLAYLISTCONTAINER_H
#define PLAYLISTCONTAINER_H
#include "playlist.h"
#include "song.h"

class PlayListContainer
{
private:

    QVector<Playlist> m_list;

public:
    typedef QVector<Playlist>::iterator iterator;
    typedef QVector<Playlist>::const_iterator const_iterator;

    PlayListContainer();
    void addPlayList(const Playlist &list);
    virtual void addSong(const Song &song) = 0;

    QStringList getNames() const;
    iterator find(const QString &name);

    void clear();

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
};

#endif // PLAYLISTCONTAINER_H
