#include "getinfo.h"



User *GetInfo::get_user(const Connector &conn, QString login, QString password)
{
    //checked
    //check user existance before!
    QString query_text = QString(QStringLiteral("select MUser.id, login, Subscribe.name, subscr_end, time_listerned"
                         " from MUser left join Subscribe "
                         " on MUser.id_subscr=Subscribe.id"
                         " where login='%1' and password='%2'").arg(login).arg(password));

    qDebug() << query_text;
    QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
    User *usr = new User(list_rec[0]);
    return usr;
}

QList<Subscribe *> GetInfo::get_available_subscribes(const Connector &conn, const int id_user)
{
    //checked не предлагаем базовую, но можно, если закончились минуты выбрать ту же что и текущая.
    QString query_text = QString("select * from Subscribe "
                         "where Subscribe.id !=1");
    qDebug() << query_text;
    QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
    QList<Subscribe *> subscribes_list;

     for (int i = 0; i < list_rec.size(); ++i)
           subscribes_list.push_back(new Subscribe(list_rec[i]));
     return subscribes_list;
}

Subscribe * GetInfo::get_cur_subscribe(const Connector &conn, const int id_user)
{
    //checked
    QString query_text = QString("select * from Subscribe "
                         "where id = (select id_subscr from MUser where id = ").append(to_string(id_user)).append(")");
    qDebug() << query_text;
    QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
    QList<Subscribe *> subscribes_list;

     for (int i = 0; i < list_rec.size(); ++i)
           subscribes_list.push_back(new Subscribe(list_rec[i]));
     return subscribes_list.at(0);
}

QList<Playlist *> GetInfo::get_playlists(const Connector &conn, const int id_user)
{
    //checked
    QString query_text = QString("select Playlist.id, name, count(*) as num_track"
                                 " from Playlist left join PT on"
                                 " Playlist.id=PT.id_playlist"
                         " where Playlist.id_user = ").append(to_string(id_user)).append(" group by Playlist.id");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Playlist *> playlists_list;

    for (int i = 0; i < list_rec.size(); ++i)
          playlists_list.push_back(new Playlist(list_rec[i]));
    return playlists_list;
}

QList<Track *> GetInfo::get_tracks_by_artist(const Connector &conn, const int id_artist)
{
    //checked
    QString query_text = QString("select Track.id, Track.name, Genre.name, Track.release_date,"
                                 " Artist.name, count(*) as n_listerned, duration, file_name"
                                 " from Track join Genre on Track.id_genre=Genre.id"
                                 " join Artist on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                         " where id_artist = ").append(to_string(id_artist)).
            append(" group by Track.id, Genre.name, Track.release_date, Artist.name");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track *> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(new Track(list_rec[i]));
    return track_list;
}

QList<Track *> GetInfo::get_tracks_by_playlist(const Connector &conn, const int id_playlist)
{
    QString query_text = QString("select Track.id, Track.name, Genre.name, Track.release_date, Artist.name,"
                                 "  count(*) as n_listerned, duration, file_name"
                                 " from Track join Genre on Track.id_genre=Genre.id"
                                 " join Artist on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                                 " join PT on PT.id_track=Track.id"
                         " where id_playlist = ").append(to_string(id_playlist)).
            append(" group by Track.id, Genre.name, Track.release_date, Artist.name");

    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track *> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(new Track(list_rec[i]));
    return track_list;
}

QList<Artist *> GetInfo::get_artists_by_name(const Connector &conn, const QString name)
{
    //checked
    QString query_text = QString("select Artist.id, Artist.name, count(distinct(Track.id)),"
                                 " count(distinct(Listening.id)) as n_track"
                                 " from Artist left join Track on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                                 " where Artist.name = '").append(name).append("' group by Artist.id, Artist.name");
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Artist *> artist_list;

    for (int i = 0; i < list_rec.size(); ++i)
          artist_list.push_back(new Artist(list_rec[i]));
    return artist_list;
}

QList<Track *> GetInfo::get_tracks_by_name(const Connector &conn, const QString name)
{
    //checked
    QString query_text = QString(QStringLiteral("select Track.id, Track.name, Genre.name, Track.release_date, Artist.name,"
                                 "  count(*) as n_listerned, duration, file_name"
                                 " from Track join Genre on Track.id_genre=Genre.id"
                                 " join Artist on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                                 " join PT on PT.id_track=Track.id"
                                 " where Track.name = '%1'"
                                 " group by Track.id, Genre.name, Track.release_date, Artist.name").arg(name));

    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track *> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(new Track(list_rec[i]));
    return track_list;
}

QList<Artist *> GetInfo::get_artists_with_filter(const Connector &conn, bool popular_fl, bool ntrack_fl)
{
    //checked
    QString sort_filter = QString();
    if (popular_fl && ntrack_fl)
        sort_filter = QString(" order by listened desc, n_track desc");
    else if (popular_fl)
        sort_filter = QString(" order by listened desc");
    else if (ntrack_fl)
        sort_filter = QString(" order by n_track desc");
    QString query_text = QString("select Artist.id, Artist.name, count(distinct(Track.id)) as n_track,"
                                 " count(distinct(Listening.id)) as listened"
                                 " from Artist left join Track on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track"
                                 " group by Artist.id, Artist.name").append(sort_filter);
    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Artist *> artist_list;

    for (int i = 0; i < list_rec.size(); ++i)
          artist_list.push_back(new Artist(list_rec[i]));
    return artist_list;
}


QList<Track *> GetInfo::get_tracks_with_filter(const Connector &conn,
                                               bool popular_fl, bool ntrack_fl, GenreFlags gf)
{
    //checked
    QString find_filter = gf.getFilters();

    QString query_text = QString(QStringLiteral("select Track.id, Track.name, Genre.name, Track.release_date, Artist.name,"
                                 "  count(distinct(Listening.id)) as n_listerned, duration, file_name"
                                 " from Track join Genre on Track.id_genre=Genre.id"
                                 " join Artist on Track.id_artist=Artist.id"
                                 " left join Listening on Track.id=Listening.id_track %1"
                         " group by Track.id, Genre.name, Track.release_date, Artist.name").arg(find_filter));

    qDebug() << query_text;

   QList<QSqlRecord>  list_rec = conn.exec_select(query_text);
   QList<Track *> track_list;

    for (int i = 0; i < list_rec.size(); ++i)
          track_list.push_back(new Track(list_rec[i]));
    return track_list;
}

QString GenreFlags::getFilters()
{
    QString cond = "where";
    QString filters = QString();
    if (!pop_fl)
    {
        filters.append(QStringLiteral(" %1 Genre.name!='поп-музыка'").arg(cond));
        cond = "and";
    }
    if (!rock_fl)
    {
        filters.append(QStringLiteral(" %1 Genre.name!='рок'").arg(cond));
        cond = "and";
    }
    if (!classic_fl)
    {
        filters.append(QStringLiteral(" %1 Genre.name!='классическая'").arg(cond));
        cond = "and";
    }
    if (!indi_fl)
    {
        filters.append(QStringLiteral(" %1 Genre.name!='инди'").arg(cond));
        cond = "and";
    }
    if (!lofi_fl)
    {
        filters.append(QStringLiteral(" %1 Genre.name!='lo-fi'").arg(cond));
        cond = "and";
    }
    if (!rep_fl)
    {
        filters.append(QStringLiteral(" %1 Genre.name!='реп'").arg(cond));
        cond = "and";
    }
    return filters;
}
