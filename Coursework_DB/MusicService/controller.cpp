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

    btn_sig = QList<int>({PLAYLIST_TRACK_SIG, DEL_PLAYLIST_SIG});
    playlistDelegate = new TableModelDelegate(this, QList<int>({2, 3}),
                                         QList<QString>({"Перейти", "Удалить"}), btn_sig);
    btn_sig = QList<int>({CHOOSE_PLAYLIST_SIG});
    addTrackDelegate = new TableModelDelegate(this, QList<int>({3}),
                                         QList<QString>({"Выбрать"}), btn_sig);

    btn_sig = QList<int>({CHOOSE_SUBSCR_SIG});
    subscrDelegate = new TableModelDelegate(this, QList<int>({3}),
                                            QList<QString>({"Выбрать"}), btn_sig);

}

void Controller::createViews()
{
    lv = new LoginView(baseWidget);
    rv = new RegView(baseWidget);
    mv = new MenuView(baseWidget);
    search_v = new SearchView(baseWidget);

    tv = new TrackView(baseWidget, trackDelegate);
    pv = new PlaylistView(baseWidget, playlistDelegate);
    sv = new SubscribeView(baseWidget, subscrDelegate);

    ld = new ListenDialog(m_player, baseWidget);
}

void Controller::setupConnections()
{
    QObject::connect(trackDelegate, SIGNAL(add_to_playlist(QVariant)), this, SLOT(addToPlaylist(QVariant)));
    QObject::connect(addTrackDelegate, SIGNAL(choose_playlist(QVariant, QVariant)), this, SLOT(endAddToPlaylist(QVariant, QVariant)));
    QObject::connect(trackDelegate, SIGNAL(play_track(QVariant)), this, SLOT(listenTrack(QVariant)));
    QObject::connect(myTrackDelegate, SIGNAL(play_track(QVariant)), this, SLOT(listenTrack(QVariant)));
    QObject::connect(myTrackDelegate, SIGNAL(del_from_playlist(QVariant, QVariant)), this, SLOT(deleteFromPlaylist(QVariant, QVariant)));

    QObject::connect(subscrDelegate, SIGNAL(change_subscr(QVariant)), this, SLOT(changeSubscribe(QVariant)));

    QObject::connect(artistDelegate, SIGNAL(show_tracks_btn_pressed(QVariant)), this, SLOT(showArtistTr(QVariant)));
    QObject::connect(playlistDelegate, SIGNAL(show_tracks_btn_pressed(QVariant)), this, SLOT(showPlaylistTr(QVariant)));
    QObject::connect(playlistDelegate, SIGNAL(del_playlist(QVariant)), this, SLOT(deletePlaylist(QVariant)));

    QObject::connect(lv, SIGNAL(try_login(QString, QString)), this, SLOT(autorize(QString, QString)));
    QObject::connect(lv, SIGNAL(btn_register_clicked()), this, SLOT(showRegView()));

    QObject::connect(rv, SIGNAL(try_register(QString, QString)), this, SLOT(registrate(QString, QString)));
    QObject::connect(rv, SIGNAL(btn_login_clicked()), this, SLOT(showLoginView()));

    QObject::connect(mv, SIGNAL(show_playlists_btn_pressed(QVariant)), this, SLOT(showPlaylistView(QVariant)));
    QObject::connect(mv, SIGNAL(show_subscrs_btn_pressed()), this, SLOT(showSubscrView()));
    QObject::connect(mv, SIGNAL(show_search_view()), this, SLOT(showSearchView()));

    QObject::connect(tv, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(pv, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(tv, SIGNAL(to_previous(AbstractView *)), this, SLOT(showPreviousView(AbstractView *)));
    QObject::connect(pv, SIGNAL(to_previous(AbstractView *)), this, SLOT(showPreviousView(AbstractView *)));
    QObject::connect(pv, SIGNAL(addAlbum(QString)), this, SLOT(addAlbum(QString)));

    QObject::connect(sv, SIGNAL(to_menu()), this, SLOT(showMenu()));

    QObject::connect(search_v, SIGNAL(to_menu()), this, SLOT(showMenu()));
    QObject::connect(search_v, SIGNAL(find_artust(QString, bool, bool)), this, SLOT(find_artust(QString, bool, bool)));

    QObject::connect(search_v, SIGNAL(find_track(QString, bool, bool, GenreFlags)),
                     this, SLOT(find_track(QString, bool, bool, GenreFlags)));
}


Controller::Controller(QWidget *baseWidget_, const Repository &repo_) : baseWidget(baseWidget_),
    repo(repo_)
{
    m_player = new QMediaPlayer();
    m_player->setVolume(70);

    this->createDelegates();
    this->createViews();

    curWidget = lv;
    curWidget->show();

    this->setupConnections();
}




void Controller::showPlaylistView(QVariant var_id)
{
    qDebug() << "Controller::showPlaylistView";
    int id = var_id.toInt();
    if (id == ALL)
    {
        curWidget->hide();

        pv->setPrevView(curWidget);
        pv->setData(repo.getPlaylists(id_user));
        pv->setDelegate(playlistDelegate);

        pv->show();
        curWidget = pv;
    }
}

void Controller::showArtistTr(QVariant id_art)
{
    int id = id_art.toInt();
    qDebug() << "showArtistTr" << id;

    curWidget->hide();

    tv->setPrevView(curWidget);
    tv->setData(repo.getTracksbyArtist(id));
    tv->setDelegate(trackDelegate);

    tv->show();
    curWidget = tv;
}

void Controller::showPlaylistTr(QVariant id_pl)
{

    int id = id_pl.toInt();
    qDebug() << "showPlaylistTr" << id;

    curWidget->hide();

    tv->setPrevView(curWidget);
    tv->setData(repo.getTracksByPlaylist(id));

    myTrackDelegate->setExtra_id(id);
    tv->setDelegate(myTrackDelegate);

    tv->show();
    curWidget = tv;
}



void Controller::showSubscrView()
{
    qDebug() << "Controller::showSubscrView";
    sv->setCurData(repo.get_curSubscr(id_user));

    curWidget->hide();
    sv->setData(repo.getSubscrs());
    sv->show();
    curWidget = sv;
}

void Controller::showSearchView()
{
    curWidget->hide();
    search_v->show();
    curWidget = search_v;
}

void Controller::showPreviousView(AbstractView *prev)
{
    if (prev == mv)
        showMenu(); //this is to update user info every time
    else
    {
       curWidget->hide();
    }
    prev->show();
    curWidget = prev;

}

void Controller::showMenu()
{
    curWidget->hide();
    mv->setUserInfo(repo.get_user(id_user));
    mv->show();
    curWidget = mv;
}

void Controller::autorize(QString login, QString password)
{
    AbstractTableData *user = repo.get_user(login, password);
    if (user != NULL)
    {
        id_user = user->getId().toInt();
        showMenu();
    }
    else
        QMessageBox::warning(lv, "Ошибка", "Неверный логин или пароль");

}

void Controller::registrate(QString login, QString password)
{
    AbstractTableData *user = repo.add_user(login, password);
    if (user != NULL)
    {
            id_user = user->getId().toInt();
            showMenu();
    }
    else
        QMessageBox::warning(lv, "Ошибка", QStringLiteral("Пользователь с логином %1 уже существует").arg(login));
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
    search_v->setArtistModel();

    if (name == QString())
        search_v->setData(repo.getArtists(popular_fl, ntrack_fl));
    else
        search_v->setData(repo.searchArtists(name));
    search_v->setDelegate(artistDelegate);
}

void Controller::find_track(QString name, bool popular_fl, bool date_fl, GenreFlags gf)
{
    qDebug() << "Controller::find_track"<<name << popular_fl << date_fl;
     search_v->setTrackModel();

    if (name == QString())
        search_v->setData(repo.getTracks(popular_fl, date_fl, gf));
    else
        search_v->setData(repo.searchTracks(name));
    search_v->setDelegate(trackDelegate);
}

void Controller::addToPlaylist(QVariant track_id)
{
    int id= track_id.toInt();
     qDebug() << "Controller::addToPlaylist track with id "<<track_id;
     curWidget->hide();

     pv->setPrevView(curWidget);
     pv->setData(repo.getPlaylists(id_user));

     addTrackDelegate->setExtra_id(track_id);
     pv->setDelegate(addTrackDelegate);

     pv->show();
     curWidget = pv;
}

void Controller::listenTrack(QVariant track_id)
{
    qDebug() << "listenTrack called";
    if (repo.addListening(id_user, track_id.toInt()) == false) //adds listening and adds time listened of this user
            QMessageBox::warning(lv, "Ошибка", "Недостаточный баланс врмемени для прослушивания этого трека");
    else
    {
        AbstractTableData *track = curWidget->getById(track_id);
        if (track == NULL)
            qDebug() << "track = NULL";
        QList<QVariant> track_data = track->getVarList();
       QString file_path = QStringLiteral("/home/julia/MS_files/%1").arg(track_data.at(6).toString());
       qDebug() << file_path;

        m_player->setMedia(QUrl::fromLocalFile(file_path));
        m_player->play();
        ld->setText(track_data.at(0).toString());
        ld->show();
    }


}

void Controller::endAddToPlaylist(QVariant pl_id, QVariant track_id)
{
    qDebug() << "endAddToPlaylist called" << pl_id << track_id;
    repo.addTrackToPlaylist(pl_id.toInt(), track_id.toInt());

    pv->setData(repo.getPlaylists(id_user));
    pv->show();

}

void Controller::deleteFromPlaylist(QVariant pl_id, QVariant track_id)
{
    qDebug() << "deleteFromPlaylist called" << pl_id << track_id;
    repo.deleteFromPlaylist(pl_id.toInt(), track_id.toInt());

    tv->setData(repo.getTracksByPlaylist(pl_id.toInt()));
    tv->show();
}

void Controller::changeSubscribe(QVariant id)
{
    qDebug() << "changeSubscribe called" << id;
    repo.changeSubscribe(id_user, id.toInt());
    sv->setCurData(repo.get_curSubscr(id_user));
    sv->show();
}

void Controller::addAlbum(QString name)
{
    qDebug() << "addAlbum called" << name;
    if (repo.addAlbum(id_user, name)==false)
        QMessageBox::warning(pv, "Ошибка", "Имя плейлиста повторяется или превышен лимит в 6 плейлистов.");

    pv->setData(repo.getPlaylists(id_user));
    pv->show();
}

void Controller::deletePlaylist(QVariant id)
{
    qDebug() << "deletePlaylist called" << id;
    repo.deletePlaylist(id.toInt());

    pv->setData(repo.getPlaylists(id_user));
    pv->show();
}
