#include "track.h"

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
    qDebug() << id << name << id_genre << release_date << id_artist;
}
