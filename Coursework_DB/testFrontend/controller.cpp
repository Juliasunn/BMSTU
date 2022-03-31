#include "controller.h"

Controller::Controller()
{
    QList<int> btn_sig = QList<int>({TRACK_SIG});
    artistDelegate = new TableModelDelegate(NULL, QList<int>({3}), QList<QString>({"Показать треки"}), btn_sig);

    cur_artists = QList<AbstractTableModel *>();
    QList<QString> headerList = QList<QString>({" имя ", " всего треков ", " прослушиваний "});
    QTrackTableModel *artistTable = new QTrackTableModel(cur_artists, headerList, 1);

    av = new ArtistView(NULL, artistTable, artistDelegate);

}

QList<AbstractTableModel *> getArtists()
{
    QList<AbstractTableModel *> artistList;
    artistList.push_back(new Artist("Lil Peep", 78, 1200687));
    artistList.push_back(new Artist("Nirvana", 135, 34567820));
    artistList.push_back(new Artist("Lady Gaga", 212, 100056743));

    return artistList;
}

void Controller::showArtistView(QVariant var_id)
{
    qDebug() << "Controller::showArtistView" << var_id;
    int id = var_id.toInt();

    if (var_id == 1)
    {
        qDebug() << "getting artisis 1";
        cur_artists = getArtists();
    }
    else if (var_id == 3)
    {
        qDebug() << "getting artisis 3";
        cur_artists = QList<AbstractTableModel *>();
        cur_artists.push_back(new Artist("Beyonce", 234, 1345897));
        cur_artists.push_back(new Artist("Melani Martinez", 66, 235221));
        cur_artists.push_back(new Artist("Hozier", 123, 306786));
        cur_artists.push_back(new Artist("Kizaru", 58, 22242));
    }
    else
        return;

    av->setData(cur_artists);
    av->show();

}

void Controller::showPlaylistView(QVariant var_id)
{
    qDebug() << "Controller::showPlaylistView";
}

void Controller::showTrackView(QVariant var_id, int type)
{
    qDebug() << "Controller::showTracklistView";
}
