#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "DataStructures/artist.h"
#include "DataStructures/track.h"
#include "DataStructures/subscribe.h"
#include "DataStructures/user.h"

class Repository
{
public:
    Repository();

    QList<AbstractTableData *> getSubscrs();

    AbstractTableData *get_user(QString login, QString password);
    AbstractTableData *get_curSubscr();
    QList<AbstractTableData *> getArtists();
    QList<AbstractTableData *> getTracks();

    QList<AbstractTableData *> getPlaylists();
};

#endif // REPOSITORY_H
