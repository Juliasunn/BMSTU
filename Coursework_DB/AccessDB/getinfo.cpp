#include "getinfo.h"



QList<Subscribe> GetInfo::get_available_subscribes(const Connector &conn, const int id_user)
{
    QString query_text = QString("select * from Subscribe "
                         "where id != (select id_subscr from MUser where id = '").append(to_string(id_user)).append("')");
    qDebug() << query_text;
    QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
    QList<Subscribe> subscribes_list;

     for (int i = 0; i < list_rec.size(); ++i)
           subscribes_list.push_back(Subscribe(list_rec[i]));
     return subscribes_list;
}

QList<Playlist> GetInfo::get_playlists(const Connector &conn, const int id_user)
{
    QString query_text = QString("select * from Playlist "
                         "where id_user = '").append(to_string(id_user)).append("'");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Playlist> playlists_list;

    for (int i = 0; i < list_rec.size(); ++i)
          playlists_list.push_back(Playlist(list_rec[i]));
    return playlists_list;
}

QList<Track> GetInfo::get_tracks_by_artist(const Connector &conn, const int id_artist)
{
    QString query_text = QString("select * from Track "
                         "where id_artist = '").append(to_string(id_artist)).append("'");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(Track(list_rec[i]));
    return track_list;
}

QList<Track> GetInfo::get_tracks_by_playlist(const Connector &conn, const int id_playlist)
{
    QString query_text = QString("select * from Track join PT on Track.id=PT.id_track "
                         "where id_playlist = ").append(to_string(id_playlist));
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(Track(list_rec[i]));
    return track_list;
}

QList<Artist> GetInfo::get_artists_by_name(const Connector &conn, const QString name)
{
    QString query_text = QString("select * from Artist "
                         "where name = '").append(name).append("'");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Artist> artist_list;

    for (int i = 0; i < list_rec.size(); ++i)
          artist_list.push_back(Artist(list_rec[i]));
    return artist_list;
}