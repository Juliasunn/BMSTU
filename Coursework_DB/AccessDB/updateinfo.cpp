#include "updateinfo.h"

bool UpdateInfo::update_listern_time(Connector &conn, int id_user, int new_listern_time)
{
    QString query_text = QString(" update MUser"
                                 " set minutes\_listerned = ").append(to_arg(new_listern_time)). \
                                 append(" where id = ").append(to_arg(id_user)).append(";");

    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}

bool UpdateInfo::update_listern_time(Connector &conn, int id_user)
{
    QString query_text = QString(" update MUser"
                                 " set minutes\_listerned = '0' where id = "). \
                                 append(to_arg(id_user)).append(";");

    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}

bool UpdateInfo::update_subscribe(Connector &conn, int id_user, int new_subscr_id, int num_month)
{

    QString query_text = QString(" update MUser"
                                 " set minutes\_listerned = '0'"
                                 ", id_subscribe = ").append(to_arg(new_subscr_id)). \
                                 append(", subscr_end = CURRENT_DATE + interval(").append(to_string(num_month)). \
                                 append(" month)  where id = ").append(to_arg(id_user)).append(";");



    qDebug() << query_text;
    return (conn.exec_non_query(query_text));
}
