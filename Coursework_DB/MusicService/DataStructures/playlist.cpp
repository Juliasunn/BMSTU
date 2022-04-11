#include "playlist.h"

QVariant Playlist::getId() const
{
    return id;
}

Playlist::Playlist()
{
    
}

Playlist::~Playlist()
{
    qDebug() << "Playlist destructor";
}

Playlist::Playlist(const QSqlRecord &rec)
{
    qDebug() << "Playlist called";
    id = rec.value(0);
    name = rec.value(1);
    num_track = rec.value(2);
   // id_user = rec.value(3);
    qDebug() << id << name << num_track;
}

QList<QVariant> Playlist::getVarList() const
{
    return QList<QVariant>({name, num_track});

}
