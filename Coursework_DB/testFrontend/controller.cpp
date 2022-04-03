#include "controller.h"

void Controller::createDelegates()
{
    QList<int> btn_sig = QList<int>({LISTERN_SIG, ADD_TO_PLAYLIST_SIG});
    trackDelegate = new TableModelDelegate(this, QList<int>({5,6}),
                                          QList<QString>({"Играть", "Добавить"}), btn_sig);

    btn_sig = QList<int>({LISTERN_SIG, DEL_FROM_PLAYLIST_SIG});
    myTrackDelegate = new TableModelDelegate(this, QList<int>({5,6}),
                                          QList<QString>({"Играть", "Удалить"}), btn_sig);
    btn_sig = QList<int>({ARTIST_TRACK_SIG});
    artistDelegate = new TableModelDelegate(this, QList<int>({3}),
                           QList<QString>({"Показать треки"}), btn_sig);

    btn_sig = QList<int>({PLAYLIST_TRACK_SIG, PLAYLIST_TRACK_SIG});
    playlistDelegate = new TableModelDelegate(this, QList<int>({2, 3}),
                                         QList<QString>({"Перейти", "Удалить"}), btn_sig);
    btn_sig = QList<int>({PLAYLIST_TRACK_SIG, PLAYLIST_TRACK_SIG});
    addTrackDelegate = new TableModelDelegate(this, QList<int>({3}),
                                         QList<QString>({"Выбрать"}), btn_sig);

    btn_sig = QList<int>({CHOOSE_SUBSCR_SIG});
    subscrDelegate = new TableModelDelegate(this, QList<int>({3}),
                                            QList<QString>({"Выбрать"}), btn_sig);

}

void Controller::createViews()
{
    QTrackTableModel *artistTable = new QTrackTableModel(cur_artists,
                             QList<QString>({" имя ", " всего треков ", " прослушиваний "}), 1);
    QTrackTableModel *playlistsTable = new QTrackTableModel(cur_playlists,
                             QList<QString>({" название ", " всего треков "}), 2);
    QTrackTableModel *trackTable = new QTrackTableModel(cur_tracks,
                             QList<QString>({" название ", " жанр ", " релиз ", " исполнитель ", " прослушиваний "}), 2);
    QTrackTableModel *subscrTable = new QTrackTableModel(cur_subscribes,
                             QList<QString>({" название ", " руб/мес ", " минут/мес "}), 1);

    lv = new LoginView(baseWidget);
    rv = new RegView(baseWidget);
    mv = new MenuView(baseWidget);
    search_v = new SearchView(baseWidget, artistTable, trackTable);

    av = new ArtistView(baseWidget, artistTable, artistDelegate);
    tv = new TrackView(baseWidget, trackTable, trackDelegate);
    pv = new PlaylistView(baseWidget, playlistsTable, playlistDelegate);
    sv = new SubscribeView(baseWidget, subscrTable, subscrDelegate);

}

void Controller::setupConnections()
{
    QObject::connect(trackDelegate, SIGNAL(show_artists_btn_pressed(QVariant)), this, SLOT(showArtistView(QVariant)));
    QObject::connect(trackDelegate, SIGNAL(add_to_playlist(QVariant)), this, SLOT(addToPlaylist(QVariant)));

    QObject::connect(artistDelegate, SIGNAL(show_tracks_btn_pressed(QVariant)), this, SLOT(showArtistTr(QVariant)));
    QObject::connect(playlistDelegate, SIGNAL(show_tracks_btn_pressed(QVariant)), this, SLOT(showPlaylistTr(QVariant)));

    QObject::connect(lv, SIGNAL(try_login(QString, QString)), this, SLOT(autorize(QString, QString)));
    QObject::connect(lv, SIGNAL(btn_register_clicked()), this, SLOT(showRegView()));

    QObject::connect(rv, SIGNAL(try_register(QString, QString)), this, SLOT(registrate(QString, QString)));
    QObject::connect(rv, SIGNAL(btn_login_clicked()), this, SLOT(showLoginView()));

    QObject::connect(mv, SIGNAL(show_artists_btn_pressed(QVariant)), this, SLOT(showArtistView(QVariant)));
    QObject::connect(mv, SIGNAL(show_playlists_btn_pressed(QVariant)), this, SLOT(showPlaylistView(QVariant)));
    QObject::connect(mv, SIGNAL(show_tracks_btn_pressed(QVariant, int)), this, SLOT(showTrackView(QVariant, int)));
    QObject::connect(mv, SIGNAL(show_subscrs_btn_pressed()), this, SLOT(showSubscrView()));
    QObject::connect(mv, SIGNAL(show_search_view()), this, SLOT(showSearchView()));

    QObject::connect(av, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(tv, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(pv, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(sv, SIGNAL(to_menu()), this, SLOT(showMenu()));

    QObject::connect(search_v, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(search_v, SIGNAL(find_artust(QString, bool, bool)), this, SLOT(find_artust(QString, bool, bool)));

    QObject::connect(search_v, SIGNAL(find_track(QString, bool, bool, GenreFlags)),
                     this, SLOT(find_track(QString, bool, bool, GenreFlags)));
}


Controller::Controller(QWidget *baseWidget_) : baseWidget(baseWidget_),
    cur_artists(QList<AbstractTableModel *>()), cur_tracks(QList<AbstractTableModel *>()),
    cur_playlists(QList<AbstractTableModel *>()), user(NULL)
{
    this->createDelegates();
    this->createViews();

    rv->hide();
    mv->hide();
    av->hide();
    tv->hide();
    pv->hide();
    sv->hide();
    search_v->hide();


    curWidget = lv;
    this->setupConnections();
}

QList<AbstractTableModel *> getSubscrs()
{
    QList<AbstractTableModel *> subscrsList;

    return subscrsList;
}

AbstractTableModel *get_user(QString login, QString password)
{
    return new User();

}

QList<AbstractTableModel *> getArtists()
{
    QList<AbstractTableModel *> artistList;
    artistList.push_back(new Artist("Lil Peep", 78, 1200687));
    artistList.push_back(new Artist("Nirvana", 135, 34567820));
    artistList.push_back(new Artist("Lady Gaga", 212, 100056743));
    artistList.push_back(new Artist("Beyonce", 234, 1345897));
    artistList.push_back(new Artist("Melani Martinez", 66, 235221));
    artistList.push_back(new Artist("Hozier", 123, 306786));
    artistList.push_back(new Artist("Kizaru", 58, 22242));

    return artistList;
}

QList<AbstractTableModel *> getTracks()
{
    QList<AbstractTableModel *> trackList;
    trackList.push_back(new Track("Sweather Weather", "rock", "27.02.2001", "Sia", 1245, 1));
    trackList.push_back(new Track("Gong Gang", "rock-n-roll", "17.05.2015", "Anny", 12, 2));
    trackList.push_back(new Track("Chendelier", "pop", "05.10.2014", "Lauce", 987, 3));

    return trackList;
}

QList<AbstractTableModel *> getPlaylists()
{
    QList<AbstractTableModel *> playlistList;
    playlistList.push_back(new Playlist("Chill", 26));
    playlistList.push_back(new Playlist("For party", 98));
    playlistList.push_back(new Playlist("Favourites", 45));

    return playlistList;
}

void Controller::showArtistView(QVariant var_id)
{
    qDebug() << "Controller::showArtistView" << var_id;
    int id = var_id.toInt();

    if (var_id == ALL)
    {
        cur_artists = getArtists();
        curWidget->hide();
        av->setData(cur_artists);
        av->show();
        curWidget = av;
    }
}

void Controller::showPlaylistView(QVariant var_id)
{
    qDebug() << "Controller::showPlaylistView";
    int id = var_id.toInt();
    if (id == ALL)
    {
        cur_playlists = getPlaylists();
        curWidget->hide();
        pv->setData(cur_playlists);
        pv->setDelegate(playlistDelegate);
        pv->show();
        curWidget = pv;
    }
}

void Controller::showArtistTr(QVariant id_art)
{
    int id = id_art.toInt();
    qDebug() << "showArtistTr" << id;

    cur_tracks = getTracks();
    curWidget->hide();
    tv->setData(cur_tracks);
    tv->setDelegate(trackDelegate);
    tv->show();
    curWidget = tv;
}

void Controller::showPlaylistTr(QVariant id_pl)
{

    int id = id_pl.toInt();
    qDebug() << "showPlaylistTr" << id;

    cur_tracks = getTracks();
    curWidget->hide();
    tv->setData(cur_tracks);
    tv->setDelegate(myTrackDelegate);
    tv->show();
    curWidget = tv;
}



void Controller::showSubscrView()
{
    qDebug() << "Controller::showSubscrView";
   // int id = var_id.toInt();
   // if (id == ALL)
   // {
        cur_subscribes = getSubscrs(); //model->getSubscr();
        curWidget->hide();
        sv->setData(cur_subscribes);
        sv->show();
        curWidget = sv;
        // }
}

void Controller::showSearchView()
{
    curWidget->hide();
    search_v->show();
    curWidget = search_v;
}

void Controller::showMenu()
{
    curWidget->hide();
    mv->show();
    curWidget = mv;
}

void Controller::autorize(QString login, QString password)
{
    user = get_user(login, password);
    if (user)
        showMenu();
}

void Controller::registrate(QString login, QString password)
{
    user = get_user(login, password);
    if (user)
        showMenu();
}

void Controller::showRegView()
{
    curWidget->hide();
    rv->show();
    curWidget = rv;
}

void Controller::showLoginView()
{
    curWidget->hide();
    lv->show();
    curWidget = lv;
}

void Controller::find_artust(QString name, bool popular_fl, bool ntrack_fl)
{
    qDebug() << "Controller::find_artust"<<name << popular_fl << ntrack_fl;
    cur_artists = getArtists();

    QTrackTableModel artistTable(cur_artists,
                             QList<QString>({" имя ", " всего треков ", " прослушиваний "}), 1);
    search_v->setArtistModel();

    search_v->setData(cur_artists);
    search_v->setDelegate(artistDelegate);
}

void Controller::find_track(QString name, bool popular_fl, bool date_fl, GenreFlags)
{
    qDebug() << "Controller::find_track"<<name << popular_fl << date_fl;
    cur_tracks = getTracks();

    search_v->setTrackModel();

    search_v->setData(cur_tracks);
    search_v->setDelegate(trackDelegate);
}

void Controller::addToPlaylist(QVariant var_id)
{
    int id = var_id.toInt();
     qDebug() << "Controller::addToPlaylist"<<id;
     cur_playlists = getPlaylists();
     curWidget->hide();
     pv->setData(cur_playlists);
     pv->setDelegate(addTrackDelegate);
     pv->show();
     curWidget = pv;
}
