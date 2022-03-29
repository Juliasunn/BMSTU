#include "artist.h"

Artist::Artist()
{

}

Artist::Artist(QSqlRecord &artist_rec)
{
    qDebug() << "Artist called";
    id = artist_rec.value(0).toInt();
    name = artist_rec.value(1).toString();
    qDebug() << id << name;
}
