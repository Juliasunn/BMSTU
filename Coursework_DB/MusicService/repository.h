#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "DataStructures/artist.h"
#include "DataStructures/track.h"
#include "DataStructures/subscribe.h"
#include "DataStructures/user.h"
#include "AccessDB/connector.h"

#include "AccessDB/checkinfo.h"
#include "AccessDB/updateinfo.h"
#include "AccessDB/deleteinfo.h"
#include "AccessDB/getinfo.h"
#include "AccessDB/insertinfo.h"

class Repository
{
private:
    Connector con;
public:
    Repository(Connector &con_):con(con_){};

    QList<AbstractTableData *> getSubscrs();

    AbstractTableData *get_user(QString login, QString password);
    AbstractTableData *get_user(int id_user);

    AbstractTableData *add_user(QString login, QString password);

    AbstractTableData *get_curSubscr(int id_user);

    QList<AbstractTableData *> getArtists(bool popular_fl, bool ntrack_fl);
    QList<AbstractTableData *> searchArtists(QString name);

    QList<AbstractTableData *> getTracksByPlaylist(int id);
    QList<AbstractTableData *> getTracksbyArtist(int id);

    QList<AbstractTableData *> getTracks(bool popular_fl, bool date_fl, GenreFlags gf);
    QList<AbstractTableData *> searchTracks(QString name);

    QList<AbstractTableData *> getPlaylists(int id_user);

    bool addTrackToPlaylist(int pl_id, int track_id);
    bool deleteFromPlaylist(int pl_id, int track_id);

    bool addListening(int id_user, int id_track);
    bool changeSubscribe(int id_user, int id_subscribe);
    bool addAlbum(int id_user, QString name);
    bool deletePlaylist(int id_album);

};

#endif // REPOSITORY_H
