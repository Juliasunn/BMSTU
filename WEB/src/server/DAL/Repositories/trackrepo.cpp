#include "include/trackrepo.h"


Track TrackRepo::getTrack(int id)
{
    return db->getTrack(id);
}

Track TrackRepo::getTrack(const std::string &uuid)
{
    return db->getTrack(uuid);
}

std::vector<Track> TrackRepo::getTracks()
{
    qDebug()<< "TrackRepo::getTracks()";
    return db->getTracks();
}

std::vector<Track> TrackRepo::getTracksByName(const std::string name_tr)
{
    return db->getTracks(name_tr);
}

std::vector<Track> TrackRepo::getTracksDateOrder()
{
    return db->getSortedTracks(T_DATE);
}

std::vector<Track> TrackRepo::getFilteredTracks(Genre g)
{
    return db->getFilteredTracks(g);
}
