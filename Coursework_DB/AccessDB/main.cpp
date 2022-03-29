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
    //QString login("Anna");
   // CheckInfo::is_login_taken(con, login);
   // CheckInfo::is_song_in_album(con, 3, 8);

  //  UpdateInfo::update_listern_time(con, 3, 19);
  //  UpdateInfo::update_listern_time(con, 3);
   // UpdateInfo::update_subscribe(con, 3, 1, 5);

    //InsertInfo::insert_listerning(con, 1, 4);
   // InsertInfo::insert_listerning(con, 2, 1);
   // InsertInfo::insert_listerning(con, 1, 2);

   // GetInfo::get_tracks_by_artist(con, 1);
   // GetInfo::get_artists_by_name(con, "Lil Peep");
   // GetInfo::get_available_subscribes(con, 2);
    //GetInfo::get_playlists(con, 1);
   // GetInfo::get_tracks_by_playlist(con, 3);

    QStringList numbers;
    numbers << "One" << "Two" << "Three" << "Four" << "Five";

    QAbstractItemModel *model = new QStringListModel(numbers);
    QListView *view = new QListView;
    view->setModel(model);
    view->show();

    return a.exec();
}
