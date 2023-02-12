#include "include/listenrepo.h"


std::vector<Listening> ListenRepo::getListeningsTrack(int id_track)
{
    return db->getListeningsTrack(id_track);
}

int ListenRepo::counListenings(int id_track)
{
    return db->counListenings(id_track);
}

std::vector<Listening> ListenRepo::getListeningsUser(int id_user)
{
    return db->getListeningsUser(id_user);
}

bool ListenRepo::addListening(int id_user, int id_track)
{
    return db->addListening(id_user, id_track);
}
