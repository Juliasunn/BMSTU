#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"

TableModelDelegate *createTrackTable(QTableView *tableView)
{
    QList<AbstractTableModel *> trackList;
    trackList.push_back(new Track("name1", "rock", "27.02.2001", "Sia", 1245, 1));
    trackList.push_back(new Track("name2", "rock-n-roll", "17.05.2015", "Anny", 12, 2));
    trackList.push_back(new Track("name3", "pop", "05.10.2014", "Lauce", 987, 3));

    QList<QString> headerList = QList<QString>({" название ", " жанр ", " релиз ", " исполнитель ", " прослушано "});

    QTrackTableModel *track_table = new QTrackTableModel(trackList, headerList, 2);
    QList<int> btn_sig = QList<int>({ARTIST_SIG, PLAYLIST_SIG});
    TableModelDelegate *tr_delegate = new TableModelDelegate(NULL, QList<int>({5,6}),
                                                             QList<QString>({"Play", "Add"}), btn_sig);
    //TODO: сделать что то с освобождениеинамической памяти из под элементов листа!

    tableView->setModel(track_table);
    tableView->setItemDelegate(tr_delegate);
    return tr_delegate;

}

//void createArtistTable(QTableView *tableView)
//{
 //   QList<AbstractTableModel *> artistList;
 //   artistList.push_back(new Artist("Lil Peep", 78, 1200687, 1));
 //   artistList.push_back(new Artist("Nirvana", 135, 34567820, 2));
 //   artistList.push_back(new Artist("Lady Gaga", 212, 100056743, 3));

  //  QList<QString> headerList = QList<QString>({" имя ", " всего треков ", " прослушиваний "});

 //   QTrackTableModel *artist_table = new QTrackTableModel(artistList, headerList, 1);
  //  TableModelDelegate *artist_delegate = new TableModelDelegate(NULL, QList<int>({3}), QList<QString>({"Показать треки"}));
    //TODO: сделать что то с освобождениеинамической памяти из под элементов листа!

   // tableView->setModel(artist_table);
  //  tableView->setItemDelegate(artist_delegate);
    //tableView->resizeRowsToContents();
//}

//void createPlaylistTable(QTableView *tableView)
//{
 //   QList<AbstractTableModel *> playlistList;
 //   playlistList.push_back(new Playlist("Chill", 26));
 //   playlistList.push_back(new Playlist("For party", 98));
  //  playlistList.push_back(new Playlist("Favourites", 45));

  //  QList<QString> headerList = QList<QString>({" название ", " всего треков "});

  //  QTrackTableModel *playlist_table = new QTrackTableModel(playlistList, headerList, 1);
  //  TableModelDelegate *playlist_delegate = new TableModelDelegate(NULL, QList<int>({2}), QList<QString>({"Перейти"}));
    //TODO: сделать что то с освобождениеинамической памяти из под элементов листа!

  //  tableView->setModel(playlist_table);
  //  tableView->setItemDelegate(playlist_delegate);
  //  tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);





   TableModelDelegate *tr_delegate = createTrackTable(ui->tableViewTrack);
   Controller *control = new Controller();
   QObject::connect(tr_delegate, SIGNAL(show_artists_btn_pressed(QVariant)), control, SLOT(showArtistView(QVariant)));
  // QObject::connect(tr_delegate, SIGNAL(show_artists_btn_pressed(QVariant)), control, SLOT(showPlaylistView(QVariant)));
   //QObject::connect(tr_delegate, SIGNAL(show_artists_btn_pressed(QVariant)), control, SLOT(showArtistView(QVariant)));

  // createArtistTable(ui->tableViewArtist);
  // createPlaylistTable(ui->tableViewPlaylist);
}

MainWindow::~MainWindow()
{
    delete ui;
}

