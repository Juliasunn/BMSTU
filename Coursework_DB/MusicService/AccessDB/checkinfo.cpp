#include "checkinfo.h"




bool CheckInfo::is_user_exist(const Connector &conn, QString login, QString password)
{
    //checked
    QString query_text = QString(QStringLiteral("select *"
                         " from MUser where login='%1' and password='%2'").arg(login).arg(password));

    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return false;
    return true;
}

bool CheckInfo::is_subscribe_expiled(Connector &conn, int user_id)
{
    //checked only on false example
    QString query_text = QString(QStringLiteral("select *"
                         " from MUser where CURRENT_DATE>subscr_end and MUser.id=%1").arg(user_id));

    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return false; //не истекла
    return true; //истекла
}

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
    QString query_text = QString(QStringLiteral("select * from PT"
                         " where id_playlist = %1 and id_track = %2").arg(album_id).arg(track_id));
    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return false;
    return true;
}

bool CheckInfo::check_time_limit(Connector &conn, int user_id, int track_id)
{
    //checked
    QString query_text = QString(QStringLiteral("select * from MUser where id =%1 and"
    " (select max_time from Subscribe join MUser on MUser.id_subscr=Subscribe.id where MUser.id =%1)-time_listerned"
                                                " >(select duration from Track where Track.id=%2)").arg(user_id).arg(track_id));
    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) == 0)
        return false;
    return true;
}

bool CheckInfo::check_album_limit(Connector &conn, int user_id)
{
    QString query_text = QString("select count(*) from Album where id_user = '").append(to_string(user_id)).append("';");

    qDebug() << query_text;
    if ((conn.exec_select(query_text).size()) < 5)
        return true;
    return false;

}
