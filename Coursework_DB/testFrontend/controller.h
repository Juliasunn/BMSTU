#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "tablemodeldelegate.h"

#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "DataStructures/artist.h"
#include "DataStructures/track.h"
#include "DataStructures/subscribe.h"
#include "DataStructures/user.h"

#include "Views/loginview.h"
#include "Views/regview.h"
#include "Views/menuview.h"
#include "Views/searchview.h"

#include "Views/artistview.h"
#include "Views/trackview.h"
#include "Views/playlistview.h"

#include "Views/subscribeview.h"


#include <QObject>
#define PLAYLIST_T 1
#define ARTIST_T 2



class Controller : public QObject
{
    Q_OBJECT
private:
    QWidget *curWidget; //виджет, показанный в данный момент

    ArtistView *av;
    MenuView *mv;
    QWidget *baseWidget;
    PlaylistView *pv;
    TrackView *tv;
    SubscribeView *sv;
    SearchView *search_v;
    LoginView *lv;
    RegView *rv;

    AbstractTableModel *user; //пользователь в системе, до входа NULL

    QList <AbstractTableModel *> cur_tracks;
    QList <AbstractTableModel *> cur_playlists;
    QList <AbstractTableModel *> cur_artists;
    QList <AbstractTableModel *> cur_subscribes;

    TableModelDelegate *trackDelegate, *myTrackDelegate;
    TableModelDelegate *playlistDelegate;
    TableModelDelegate *artistDelegate;
    TableModelDelegate *subscrDelegate;
    TableModelDelegate *addTrackDelegate;

    void createDelegates();
    //void createTableModels();
    void createViews();
    void setupConnections();
public:
    Controller(QWidget *widget);
public slots:
    void showArtistView(QVariant var_id);
    void showPlaylistView(QVariant var_id);

   // void showTrackView(QVariant var_id, int type);
    void showArtistTr(QVariant id_art);
    void showPlaylistTr(QVariant id_pl);

    void showSubscrView();//users id to find available subscr
    void showSearchView();

    void showMenu();
    void autorize(QString login, QString password); //after autorization btn clicked
    void registrate(QString, QString);
    void showRegView();
    void showLoginView();

    void find_artust(QString name, bool popular_fl, bool ntrack_fl);
    void find_track(QString name, bool popular_fl, bool date_fl, GenreFlags);

    void addToPlaylist(QVariant var_id);


};

#endif // CONTROLLER_H
