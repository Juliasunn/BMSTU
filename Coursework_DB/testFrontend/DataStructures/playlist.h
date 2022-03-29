#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>

class Playlist
{
private:
    int id;
    QString name;
    int id_user;
public:
    Playlist();
    Playlist(const QSqlRecord &rec);

};

#endif // PLAYLIST_H
