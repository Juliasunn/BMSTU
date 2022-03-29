#include "track.h"

Track::Track()
{

}

Track::Track(QSqlRecord &track_rec)
{
    qDebug() << "Track called";
    id = track_rec.value(0).toInt();
    name = track_rec.value(1).toString();
    id_genre = track_rec.value(2).toInt();
    release_date = track_rec.value(3).toDate();
    id_artist = track_rec.value(4).toInt();
    qDebug() << id << name << id_genre << release_date << id_artist;
}
