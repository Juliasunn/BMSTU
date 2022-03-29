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
    int id;
    QString name;
    int id_genre;
    QDate release_date;
    int id_artist;
public:
    Track();
    Track(QSqlRecord &track_rec);
};

#endif // TRACK_H
