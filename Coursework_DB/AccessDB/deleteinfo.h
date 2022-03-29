#ifndef DELETEINFO_H
#define DELETEINFO_H
#include "connector.h"

class DeleteInfo
{
public:
    DeleteInfo() = delete;
    static bool delete_track(Connector &conn, int id_playlist, int id_track);
    static bool delete_playlist(Connector &conn, int id_playlist);

};

#endif // DELETEINFO_H
