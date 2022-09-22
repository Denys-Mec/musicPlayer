#include "playlist.h"

Playlist::Playlist()
{

}

Playlist::Playlist(const QString &name)
    :m_name(name)
{

}


Playlist::~Playlist()
{
    m_list.clear();
}

int Playlist::size() const
{
    return m_list.size();
}
void Playlist::setName(const QString &name)
{
    m_name = name;
}

QString Playlist::getName() const
{
    return m_name;
}

void Playlist::addSong(const Song &song)
{
    m_list.push_back(song);
    this->sort();
}

void Playlist::deleteSong(Playlist::iterator iter)
{
    m_list.erase(iter);
}

Playlist::iterator Playlist::find(const QString &songName)
{
    auto iter {m_list.begin()};
    for(; iter != m_list.end(); ++iter){
        if(iter->getSongName() == songName)
            return iter;
    }
    return iter;
}

void Playlist::sort()
{
    qSort(m_list.begin(), m_list.end());
}

Playlist::iterator Playlist::begin() const
{
    return const_cast<Playlist::iterator>(m_list.begin());
}
Playlist::iterator Playlist::end() const
{
    return const_cast<Playlist::iterator>(m_list.end());
}
Playlist::const_iterator Playlist::cbegin() const
{
    return m_list.cbegin();
}
Playlist::const_iterator Playlist::cend() const
{
    return m_list.cend();
}
