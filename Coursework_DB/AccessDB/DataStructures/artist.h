#ifndef ARTIST_H
#define ARTIST_H
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>

class Artist
{
private:
    int id;
    QString name;
public:
    Artist();
    Artist(QSqlRecord &artist_rec);
};

#endif // ARTIST_H
