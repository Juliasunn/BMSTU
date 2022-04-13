#include "repository.h"


//CheckInfo::check_time_limit(con, 1, 3);
//QString login("Anna");
// CheckInfo::is_login_taken(con, login);
// CheckInfo::is_song_in_album(con, 3, 8);
// if (CheckInfo::is_user_exist(con, "Sam", "12345"))
//     GetInfo::get_user(con, "Sam", "12345");
//qDebug() << CheckInfo::is_subscribe_expiled(con, 1);

//UpdateInfo::update_listern_time(con, 1, 3);
//UpdateInfo::update_subscribe(con, 1, 3, 2);
// UpdateInfo::update_subscribe(con, 3, 1, 5);

//InsertInfo::insert_listerning(con, 1, 4);
// InsertInfo::insert_listerning(con, 2, 1);
// InsertInfo::insert_listerning(con, 1, 2);
// InsertInfo::insert_user(con, "Serseya", "201228");
 //InsertInfo::insert_track(con, 2, 6);
// InsertInfo::insert_playlist(con, "added1", 3);

//GetInfo::get_tracks_by_artist(con, 3);
//GetInfo::get_artists_by_name(con, "The Neiborhood");
//GetInfo::get_tracks_by_name(con, "Reflections");
// GetInfo::get_available_subscribes(con, 2);
//GetInfo::get_cur_subscribe(con, 2);
//GetInfo::get_playlists(con, 1);
//GetInfo::get_tracks_by_playlist(con, 3);

//GenreFlags gf = GenreFlags({1, 0, 1, 0, 1, 0});
//GetInfo::get_tracks_with_filter(con, 1, 1, gf);

//GetInfo::get_artists_with_filter(con, true, true);


// DeleteInfo::delete_playlist(con, 6);
// DeleteInfo::delete_track(con, 2, 1);



QList<AbstractTableData *> Repository::getSubscrs()
{
    QList<AbstractTableData *> subscrsList = GetInfo::get_available_subscribes(con, 0);
    return subscrsList;
}

AbstractTableData *Repository::get_user(QString login, QString password)
{
    if (CheckInfo::is_user_exist(con, login, password))
    {
            qDebug()<< "[Repository] user exists" << login << password;
            User *u = GetInfo::get_user(con, login, password);
            return u;
    }
    qDebug()<< "[Repository] user NOT exists" << login << password;
    return NULL;

}

AbstractTableData *Repository::get_user(int id_user)
{
    User *u = GetInfo::get_user(con, id_user);
    return u;
}

AbstractTableData *Repository::add_user(QString login, QString password)
{
    if (CheckInfo::is_login_taken(con, login) == true)
    {
        qDebug()<< "[Repository] login ALREADY exists" << login;
        return NULL;
    }
    InsertInfo::insert_user(con, login, password);
    qDebug()<< "[Repository] added user" << login << password;
    return get_user(login, password);

}

AbstractTableData *Repository::get_curSubscr(int id_user)
{
    AbstractTableData *s = GetInfo::get_cur_subscribe(con, id_user);
    return s;

}

QList<AbstractTableData *> Repository::getArtists(bool popular_fl, bool ntrack_fl)
{
    QList<AbstractTableData *> artistList = GetInfo::get_artists_with_filter(con, popular_fl, ntrack_fl);
    return artistList;
}

QList<AbstractTableData *> Repository::getTracksByPlaylist(int id)
{
    QList<AbstractTableData *> t = GetInfo::get_tracks_by_playlist(con, id);
    return t;
}

QList<AbstractTableData *> Repository::getTracksbyArtist(int id)
{
    QList<AbstractTableData *> t = GetInfo::get_tracks_by_artist(con, id);
    return t;
}

QList<AbstractTableData *> Repository::getTracks(bool popular_fl, bool date_fl, GenreFlags gf)
{
    QList<AbstractTableData *> trackList;
    qDebug() << "[Repository] getTracks" << popular_fl << date_fl;
    trackList = GetInfo::get_tracks_with_filter(con, popular_fl, date_fl, gf);

    return trackList;
}

QList<AbstractTableData *> Repository::getPlaylists(int id_user)
{
    QList<AbstractTableData *> playlistList = GetInfo::get_playlists(con, id_user);

    return playlistList;
}

bool Repository::addTrackToPlaylist(int pl_id, int track_id)
{
    if (CheckInfo::is_song_in_album(con, pl_id, track_id) == false)
    {
        qDebug()<< "[Repository] inserted track";
        InsertInfo::insert_track(con, track_id, pl_id);
        return true;
    }
    qDebug()<< "[Repository] track is already in playlist";
}

bool Repository::deleteFromPlaylist(int pl_id, int track_id)
{
    if (CheckInfo::is_song_in_album(con, pl_id, track_id) == true)
    {
        qDebug()<< "[Repository] deleted track";
        DeleteInfo::delete_track(con, pl_id, track_id);
        return true;
    }
    qDebug()<< "[Repository] track is NOT in playlist";
    return false;
}

bool Repository::addListening(int id_user, int id_track)
{
    if (CheckInfo::check_time_limit(con, id_user, id_track) == true)
    {
        qDebug()<< "[Repository] user have enough time to listen";
        InsertInfo::insert_listerning(con, id_user, id_track);
        UpdateInfo::update_listern_time(con, id_user, id_track);
        return true;

    }
    qDebug()<< "[Repository] user have NOT enough time to listen";
    return false;
}

bool Repository::changeSubscribe(int id_user, int id_subscribe)
{
    qDebug()<< "[Repository] update subscribe";
    UpdateInfo::update_subscribe(con, id_user, id_subscribe, 1);
    return true;
}

bool Repository::addAlbum(int id_user, QString name)
{
    if (CheckInfo::check_album_limit(con, id_user) == false)
    {
        qDebug() << "[Repository] user have 5 albums";
        return false;
    }
    if (CheckInfo::check_album_exists(con, id_user, name) == true)
    {
        qDebug() << "[Repository] album with this name ALREADY exists";
        return false;
    }
    InsertInfo::insert_playlist(con, name, id_user);
    qDebug()<< "[Repository] added album";
    return true;

}

bool Repository::deletePlaylist(int id_album)
{
    qDebug()<< "[Repository] deleted album";
    return DeleteInfo::delete_playlist(con, id_album);

}
