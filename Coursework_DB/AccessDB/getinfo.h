#ifndef GETINFO_H
#define GETINFO_H
#include "connector.h"
#include "DataStructures/track.h"
#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "DataStructures/subscribe.h"
class GetInfo
{
public:
    GetInfo() = delete;
    static QList<Subscribe> get_available_subscribes(const Connector &conn, const int id_user);
    static QList<Playlist> get_playlists(const Connector &conn, const int id_user);

    static QList<Track> get_tracks_by_artist(const Connector &conn, const int id_artist);
    static QList<Track> get_tracks_by_playlist(const Connector &conn, const int id_playlist);
    static QList<Artist> get_artists_by_name(const Connector &conn, const QString name);
};

#endif // GETINFO_H
