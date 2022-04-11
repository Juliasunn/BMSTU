#ifndef GETINFO_H
#define GETINFO_H
#include "connector.h"
#include "DataStructures/track.h"
#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "DataStructures/subscribe.h"
#include "DataStructures/user.h"
class GenreFlags
{
    bool pop_fl;
    bool rock_fl;
    bool classic_fl;
    bool indi_fl;
    bool lofi_fl;
    bool rep_fl;
public:
    GenreFlags(bool pop_fl_, bool rock_fl_, bool classic_fl_,
               bool indi_fl_, bool lofi_fl_, bool rep_fl_):
            pop_fl(pop_fl_), rock_fl(rock_fl_), classic_fl(classic_fl_),
            indi_fl(indi_fl_), lofi_fl(lofi_fl_), rep_fl(rep_fl_) {};
    QString getFilters();
};


class GetInfo
{
public:
    GetInfo() = delete;
    static User *get_user(const Connector &conn, QString login, QString password);
    static User *get_user(const Connector &conn, int id);

    static QList<AbstractTableData *> get_available_subscribes(const Connector &conn, const int id_user);
    static Subscribe * get_cur_subscribe(const Connector &conn, const int id_user);
    static QList<AbstractTableData *> get_playlists(const Connector &conn, const int id_user);

    static QList<AbstractTableData *> get_tracks_by_artist(const Connector &conn, const int id_artist);
    static QList<AbstractTableData *> get_tracks_by_playlist(const Connector &conn, const int id_playlist);
    static QList<AbstractTableData *> get_artists_by_name(const Connector &conn, const QString name);
    static QList<AbstractTableData *> get_tracks_by_name(const Connector &conn, const QString name);


    static QList<AbstractTableData *> get_artists_with_filter(const Connector &conn,
                                                   bool popular_fl, bool ntrack_fl);
    static QList<AbstractTableData *> get_tracks_with_filter(const Connector &conn,
                                                 bool popular_fl, bool ntrack_fl, GenreFlags gf);//TODO
};

#endif // GETINFO_H
