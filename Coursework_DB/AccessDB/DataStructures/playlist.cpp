#include "playlist.h"

Playlist::Playlist()
{

}

Playlist::Playlist(const QSqlRecord &rec)
{
    qDebug() << "Playlist called";
    id = rec.value(0).toInt();
    name = rec.value(1).toString();
    id_user = rec.value(2).toInt();
    qDebug() << id << name << id_user;
}
