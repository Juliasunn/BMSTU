#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "tablemodeldelegate.h"
#include "repository.h"
#include "listmodel.h"

#include "Views/loginview.h"
#include "Views/regview.h"
#include "Views/menuview.h"
#include "Views/searchview.h"

#include "Views/trackview.h"
#include "Views/playlistview.h"
#include "Views/subscribeview.h"


#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
private:
    Repository repo;

    AbstractView *curWidget; //виджет, показанный в данный момент

    MenuView *mv;
    QWidget *baseWidget;
    PlaylistView *pv;
    TrackView *tv;
    SubscribeView *sv;
    SearchView *search_v;
    LoginView *lv;
    RegView *rv;

    TableModelDelegate *trackDelegate, *myTrackDelegate;
    TableModelDelegate *playlistDelegate;
    TableModelDelegate *artistDelegate;
    TableModelDelegate *subscrDelegate;
    TableModelDelegate *addTrackDelegate;

    void createDelegates();
    void createViews();
    void setupConnections();
public:
    Controller(QWidget *widget);
public slots:
    void showPlaylistView(QVariant var_id);
    void showArtistTr(QVariant id_art);
    void showPlaylistTr(QVariant id_pl);

    void showSubscrView();//users id to find available subscr
    void showSearchView();
    void showPreviousView(AbstractView *prev);

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
