#include "repository.h"

Repository::Repository()
{

}

QList<AbstractTableData *> Repository::getSubscrs()
{
    QList<AbstractTableData *> subscrsList;

    subscrsList.push_back(new Subscribe("базовая", 0, 300));

    subscrsList.push_back(new Subscribe("PRO", 240, 3000));
    return subscrsList;
}

AbstractTableData *Repository::get_user(QString login, QString password)
{
    return new User("Emily Smith", "standart", "27.03.2023", 45, 16);

}

AbstractTableData *Repository::get_curSubscr()
{
    return new Subscribe("стандарнтная", 160, 1200);

}

QList<AbstractTableData *> Repository::getArtists()
{
    QList<AbstractTableData *> artistList;
    artistList.push_back(new Artist("Lil Peep", 78, 1200687));
    artistList.push_back(new Artist("Nirvana", 135, 34567820));
    artistList.push_back(new Artist("Lady Gaga", 212, 100056743));
    artistList.push_back(new Artist("Beyonce", 234, 1345897));
    artistList.push_back(new Artist("Melani Martinez", 66, 235221));
    artistList.push_back(new Artist("Hozier", 123, 306786));
    artistList.push_back(new Artist("Kizaru", 58, 22242));

    return artistList;
}

QList<AbstractTableData *> Repository::getTracks()
{
    QList<AbstractTableData *> trackList;
    trackList.push_back(new Track("Sweather Weather", "rock", "27.02.2001", "Sia", 1245, 1));
    trackList.push_back(new Track("Gong Gang", "rock-n-roll", "17.05.2015", "Anny", 12, 2));
    trackList.push_back(new Track("Chendelier", "pop", "05.10.2014", "Lauce", 987, 3));

    return trackList;
}

QList<AbstractTableData *> Repository::getPlaylists()
{
    QList<AbstractTableData *> playlistList;
    playlistList.push_back(new Playlist("Chill", 26));
    playlistList.push_back(new Playlist("For party", 98));
    playlistList.push_back(new Playlist("Favourites", 45));

    return playlistList;
}
