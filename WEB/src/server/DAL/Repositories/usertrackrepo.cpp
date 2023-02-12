#include "include/usertrackrepo.h"

std::vector<Track> UserTrackRepo::getUserTracks(int u_id)
{
    return db->getUserTracks(u_id);
}

std::vector<Track> UserTrackRepo::getUserTracks(User us)
{
    return db->getUserTracks(us.getId());
}

Track UserTrackRepo::getUserTrack(const std::string &guid, int u_id)
{
    return db->getUserTrack(guid, u_id);
}

void UserTrackRepo::deleteTrack(int t_id, int u_id)
{
    db->deleteUserTrack(t_id, u_id);
}

void UserTrackRepo::deleteTrack(const std::string &t_uuid, int u_id)
{
    Track t = db->getTrack(t_uuid);
    this->deleteTrack(t.getId(), u_id);
}

void UserTrackRepo::deleteTrack(Track track_, User us)
{
    db->deleteUserTrack(track_.getId(), us.getId());
}

void UserTrackRepo::addTrack(int t_id, int u_id)
{
    db->addTrack(t_id, u_id);
}

void UserTrackRepo::addTrack(const std::string &t_uuid, int u_id)
{
    Track t = db->getTrack(t_uuid);
    this->addTrack(t.getId(), u_id);
}

void UserTrackRepo::addTrack(Track track_, User us)
{
    db->addTrack(track_.getId(), us.getId());
}

bool UserTrackRepo::isTrackAdded(Track track_, User us)
{
    return db->isTrackAdded(track_.getId(), us.getId());
}
