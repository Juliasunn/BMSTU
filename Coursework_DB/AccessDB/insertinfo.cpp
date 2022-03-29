#include "insertinfo.h"


bool InsertInfo::insert_user(Connector &conn, QString login, QString password)
{
    QString login_arg = to_arg(login), password_arg = to_arg(password);
    QString query_text = QString("insert into MUser (id, login, password, id_subscr, subscr_end, minutes_listerned) "
                         "VALUES ((select count(*)+1 from MUser), ?, ?, ?, ?, ?)");

    qDebug() << query_text;
    QList<QVariant> params = QList<QVariant>({login_arg, password_arg, 0, "null", 0});

    return (conn.exec_param_query(query_text, params));
}

bool InsertInfo::insert_track(Connector &conn, int id_track, int id_playlist)
{
    QString query_text = QString("insert into PT (id, id_playlist, id_track) "
                         "VALUES ((select count(*)+1 from PT), ?, ?)");
    QList<QVariant> params = QList<QVariant>({id_track, id_playlist});
    qDebug() << query_text;
    return (conn.exec_param_query(query_text, params));
}

bool InsertInfo::insert_playlist(Connector &conn, QString name, int id_user)
{
    QString query_text = QString("insert into Playlist (id, name, id_user) "
                         "VALUES ((select count(*)+1 from Playlist), ?, ?)");
    QList<QVariant> params = QList<QVariant>({to_arg(name), id_user});
    qDebug() << query_text;
    return (conn.exec_param_query(query_text, params));
}

bool InsertInfo::insert_listerning(Connector &conn, int id_user, int id_track)
{
    QString query_text = QString("insert into Listening (id, lst_date, id_track, id_user) "
                         "VALUES ((select count(*)+1 from Listening), CURRENT_DATE, ?, ?)");
    qDebug() << query_text;
    QList<QVariant> params = QList<QVariant>({id_track, id_user});
    return (conn.exec_param_query(query_text, params));
}
