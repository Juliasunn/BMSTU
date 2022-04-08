#ifndef TRACK_H
#define TRACK_H
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>

class Track
{
private:
    QVariant id;
    QVariant name;
    QVariant id_genre;
    QVariant release_date;
    QVariant id_artist;
public:
    Track();
    Track(QSqlRecord &track_rec);
};

#endif // TRACK_H
