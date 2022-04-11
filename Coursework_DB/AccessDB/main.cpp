#include <QCoreApplication>
#include "checkinfo.h"
#include "updateinfo.h"
#include "deleteinfo.h"
#include "getinfo.h"
#include "insertinfo.h"

#include <QAbstractItemModel>
#include <QListView>
#include <QStringListModel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication a(argc, argv);
    Connector con;
    con.open_connection();

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



    return a.exec();
}
