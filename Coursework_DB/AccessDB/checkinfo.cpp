#include "checkinfo.h"




bool CheckInfo::is_login_taken(Connector &conn, QString &login)
{
    QString query_text = QString("select * from MUser "
                         "where login = '").append(login).append("';");
    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return false;
    return true;
}

bool CheckInfo::is_song_in_album(Connector &conn, int album_id, int track_id)
{
    QString query_text = QString("select * from PT "
                         "where playlist_id = '").append(to_string(album_id)).append(QString("' and "
                          "track_id = '")).append(to_string(track_id)).append("';");
    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return false;
    return true;
}

bool CheckInfo::check_time_limit(Connector &conn, int user_id)
{
    QString query_text = QString("select * from MUser where id = '").append(to_string(user_id)).append("' where"
                                  "time_listern <= 0;");
    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return true;
    return false;
}

bool CheckInfo::check_album_limit(Connector &conn, int user_id)
{
    QString query_text = QString("select count(*) from Album where id_user = '").append(to_string(user_id)).append("';");

    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) < 5)
        return true;
    return false;

}
