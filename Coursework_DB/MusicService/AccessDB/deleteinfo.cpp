#include "deleteinfo.h"


bool DeleteInfo::delete_track(Connector &conn, int id_playlist, int id_track)
{
    //checked
    QString query_text = QString(QStringLiteral("delete from PT"
                         " where id_playlist = %1 and id_track = %2").arg(id_playlist).arg(id_track));
    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}

bool DeleteInfo::delete_playlist(Connector &conn, int id_playlist)
{
    //checked
    QString query_text = QString(QStringLiteral("delete from PT"
                         " where id_playlist = %1").arg(id_playlist));
    qDebug() << query_text;
    conn.exec_non_query(query_text);
    query_text = QString(QStringLiteral("delete from Playlist"
                             " where id = %1").arg(id_playlist));
    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}
