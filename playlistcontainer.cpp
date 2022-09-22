#include "playlistcontainer.h"

PlayListContainer::PlayListContainer()
{

}

void PlayListContainer::addPlayList(const Playlist &list)
{
    m_list.push_back(list);
}

QStringList PlayListContainer::getNames() const
{
    QStringList list;
    for(auto e : m_list)
    {
        list.push_back(e.getName());
    }
    return list;
}

void PlayListContainer::clear()
{
    m_list.clear();
}

PlayListContainer::iterator PlayListContainer::find(const QString &name)
{
    for(auto iter{m_list.begin()}; iter != m_list.end(); ++iter)
    {
        if(iter->getName() == name)
            return iter;
    }
    return m_list.end();
}

PlayListContainer::iterator PlayListContainer::begin() const
{
    return const_cast<PlayListContainer*>(this)->m_list.begin();
}

PlayListContainer::iterator PlayListContainer::end() const
{
    return const_cast<PlayListContainer*>(this)->m_list.end();
}

PlayListContainer::const_iterator PlayListContainer::cbegin() const
{
    return m_list.cbegin();
}

PlayListContainer::const_iterator PlayListContainer::cend() const
{
    return m_list.cend();
}
