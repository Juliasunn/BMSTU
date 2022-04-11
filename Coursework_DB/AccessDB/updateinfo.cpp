#include "updateinfo.h"

bool UpdateInfo::update_listern_time(Connector &conn, int user_id, int track_id)
{
    //checked
    QString query_text = QString(QStringLiteral(" update MUser"
                                 " set time_listerned = (select time_listerned from MUser where MUser.id=%1)"
                                 " +(select duration from Track where id=%2) where MUser.id=%1").arg(user_id).arg(track_id));

    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}


bool UpdateInfo::update_subscribe(Connector &conn, int id_user, int subscr_id, int num_month)
{
    //checked
    QString query_text = QString(QStringLiteral(" update MUser"
                                 " set time_listerned = '00:00:00'"
                                 ", id_subscr = %1 , subscr_end = CURRENT_DATE + interval '%2 month'"
                                 " where MUser.id = %3").arg(subscr_id).arg(num_month).arg(id_user));



    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}
