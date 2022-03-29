#include "deleteinfo.h"


bool DeleteInfo::delete_track(Connector &conn, int id_playlist, int id_track)
{
    QString query_text = QString("delete * from PT"
                         "where id_playlist = '").append(to_string(id_playlist)).append("' and"
                         "id_track = '").append(to_string(id_track)).append("';");
    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}

bool DeleteInfo::delete_playlist(Connector &conn, int id_playlist)
{
    QString query_text = QString("delete * from PT"
                         "where id_playlist = '").append(to_string(id_playlist)).append("';");
    qDebug() << query_text;
    query_text = QString("delete * from Playlist"
                             "where id = '").append(to_string(id_playlist)).append("';");
    return (conn.exec_non_query(query_text));
}
