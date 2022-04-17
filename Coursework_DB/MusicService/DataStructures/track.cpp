#include "track.h"



QVariant Track::getName() const
{
    return name;
}

QVariant Track::getId_genre() const
{
    return genre;
}

QVariant Track::getRelease_date() const
{
    return release_date;
}

QVariant Track::getId_artist() const
{
    return artist;
}

QVariant Track::getListenings() const
{
    return listenings;
}

QList<QVariant> Track::getVarList() const
{
    return QList<QVariant>({name, genre, release_date, artist, listenings, time, file_name});
}

Track::Track()
{

}

Track::~Track()
{
    qDebug() << "Track destructor";
}

Track::Track(QSqlRecord &track_rec)
{
    qDebug() << "Track called";
    id = track_rec.value(0);
    name = track_rec.value(1);
    genre = track_rec.value(2);
    release_date = track_rec.value(3);
    artist = track_rec.value(4);
    listenings = track_rec.value(5);
    time = track_rec.value(6); //show
    file_name = track_rec.value(7);
   qDebug() << id << name << genre << release_date << artist << listenings << time << file_name;
}

QVariant Track::getId() const
{
    return id;
}
