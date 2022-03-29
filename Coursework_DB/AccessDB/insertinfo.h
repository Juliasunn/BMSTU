#ifndef INSERTINFO_H
#define INSERTINFO_H
#include "connector.h"

class InsertInfo
{
public:
    InsertInfo() = delete;
    static bool insert_user(Connector &conn, QString login, QString password);
    static bool insert_track(Connector &conn, int id_track, int id_playlist);
    static bool insert_playlist(Connector &conn, QString name, int id_user);
    static bool insert_listerning(Connector &conn, int id_user, int id_track);
};

#endif // INSERTINFO_H
