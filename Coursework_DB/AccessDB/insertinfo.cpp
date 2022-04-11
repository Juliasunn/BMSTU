#include "insertinfo.h"


bool InsertInfo::insert_user(Connector &conn, QString login, QString password)
{
    //checked
    QString login_arg = to_arg(login), password_arg = to_arg(password);
    QString query_text = QString(QStringLiteral("insert into MUser (id, login, password, id_subscr, subscr_end, minutes_listerned) "
       "VALUES ((select count(*)+1 from MUser), '%1', '%2', %3, %4, %5)").arg(login).arg(password). \
                                 arg(1).arg("(select CURRENT_DATE+interval '6 month')").arg(0));

    qDebug() << query_text;
    QList<QVariant> params = QList<QVariant>();

    return (conn.exec_param_query(query_text, params));
}

bool InsertInfo::insert_track(Connector &conn, int id_track, int id_playlist)
{
    //checked
    //check if track is not in playlist already before calling it
    QString query_text = QString(QStringLiteral("insert into PT (id, id_playlist, id_track) "
                         "VALUES ((select count(*)+1 from PT), %1, %2)").arg(id_playlist).arg(id_track));
    QList<QVariant> params = QList<QVariant>();
    qDebug() << query_text;
    return (conn.exec_param_query(query_text, params));
}

bool InsertInfo::insert_playlist(Connector &conn, QString name, int id_user)
{
    //checked
    //check if user has less then 5 playlists before
    QString query_text = QString(QStringLiteral("insert into Playlist (id, name, id_user) "
                         "VALUES ((select count(*)+1 from Playlist), '%1', %2)").arg(name).arg(id_user));
    QList<QVariant> params = QList<QVariant>();
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
