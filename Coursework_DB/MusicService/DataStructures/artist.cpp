#include "artist.h"

QVariant Artist::getId() const
{
    return id;
}

Artist::Artist()
{
    
}

Artist::~Artist()
{
    qDebug() << "Artist destructor";
}

Artist::Artist(QSqlRecord &artist_rec)
{
    qDebug() << "Artist called";
    id = artist_rec.value(0);
    name = artist_rec.value(1);
    num_track = artist_rec.value(2);
    listenings = artist_rec.value(3);
    qDebug() << id << name << num_track << listenings;
}

QList<QVariant> Artist::getVarList() const
{
    return QList<QVariant>({name, num_track, listenings});
}
