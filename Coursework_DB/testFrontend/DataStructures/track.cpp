#include "track.h"



QVariant Track::getName() const
{
    return name;
}

QVariant Track::getId_genre() const
{
    return id_genre;
}

QVariant Track::getRelease_date() const
{
    return release_date;
}

QVariant Track::getId_artist() const
{
    return id_artist;
}

QVariant Track::getListenings() const
{
    return listenings;
}

QList<QVariant> Track::getVarList() const
{
    return QList<QVariant>({name, id_genre, release_date, id_artist, listenings});
}

Track::Track()
{

}

Track::Track(QSqlRecord &track_rec)
{
    qDebug() << "Track called";
    id = track_rec.value(0);
    name = track_rec.value(1);
    id_genre = track_rec.value(2);
    release_date = track_rec.value(3);
    id_artist = track_rec.value(4);
    listenings = track_rec.value(5);
    //qDebug() << id << name << id_genre << release_date << id_artist;
}

QVariant Track::getId() const
{
    return id;
}
