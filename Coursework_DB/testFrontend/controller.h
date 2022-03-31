#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "tablemodeldelegate.h"
#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "DataStructures/artist.h"
#include "DataStructures/track.h"
#include "artistview.h"
#include <QObject>
#define PLAYLIST_T 1
#define ARTIST_T 2

class Controller : public QObject
{
    Q_OBJECT
private:
    ArtistView *av;
   // PlaylistView *pv;
   // TrackView *tv;

    QList <AbstractTableModel *> cur_tracks;
    QList <AbstractTableModel *> cur_playlists;
    QList <AbstractTableModel *> cur_artists;

    TableModelDelegate *trackDelegate;
    TableModelDelegate *playlistDelegate;
    TableModelDelegate *artistDelegate;


public:
    Controller();
public slots:
    void showArtistView(QVariant var_id);
    void showPlaylistView(QVariant var_id);
    void showTrackView(QVariant var_id, int type);


};

#endif // CONTROLLER_H
