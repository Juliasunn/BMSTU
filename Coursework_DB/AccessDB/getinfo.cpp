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
    //checked
    QString query_text = QString("select Playlist.id, name, count(*) as num_track"
                                 " from Playlist left join PT on"
                                 " Playlist.id=PT.id_playlist"
                         " where Playlist.id_user = ").append(to_string(id_user)).append(" group by Playlist.id");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Playlist> playlists_list;

    for (int i = 0; i < list_rec.size(); ++i)
          playlists_list.push_back(Playlist(list_rec[i]));
    return playlists_list;
}

QList<Track> GetInfo::get_tracks_by_artist(const Connector &conn, const int id_artist)
{
    //checked
    QString query_text = QString("select Track.id, Track.name, Genre.name, Track.release_date,"
                                 " Artist.name, count(*) as n_listerned"
                                 " from Track join Genre on Track.id_genre=Genre.id"
                                 " join Artist on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                         " where id_artist = ").append(to_string(id_artist)).
            append(" group by Track.id, Genre.name, Track.release_date, Artist.name");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(Track(list_rec[i]));
    return track_list;
}

QList<Track> GetInfo::get_tracks_by_playlist(const Connector &conn, const int id_playlist)
{
    QString query_text = QString("select Track.id, Track.name, Genre.name, Track.release_date, Artist.name,"
                                 "  count(*) as n_listerned"
                                 " from Track join Genre on Track.id_genre=Genre.id"
                                 " join Artist on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                                 " join PT on PT.id_track=Track.id"
                         " where id_playlist = ").append(to_string(id_playlist)).
            append(" group by Track.id, Genre.name, Track.release_date, Artist.name");

    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(Track(list_rec[i]));
    return track_list;
}

QList<Artist> GetInfo::get_artists_by_name(const Connector &conn, const QString name)
{
    //checked
    QString query_text = QString("select Artist.id, Artist.name, count(distinct(Track.id)),"
                                 " count(distinct(Listening.id)) as n_track"
                                 " from Artist left join Track on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                                 " where Artist.name = '").append(name).append("' group by Artist.id, Artist.name");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Artist> artist_list;

    for (int i = 0; i < list_rec.size(); ++i)
          artist_list.push_back(Artist(list_rec[i]));
    return artist_list;
}
