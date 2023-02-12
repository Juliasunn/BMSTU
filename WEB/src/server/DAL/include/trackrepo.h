#ifndef TRACKREPO_H
#define TRACKREPO_H
#include "accessordb.h"
#include "DAL_global.h"
#include <QDebug>
class DAL_EXPORT TrackRepo
{
public:
    TrackRepo(std::shared_ptr<AccessorDB> db_):db(db_){qDebug()<<"TrackRepo CONSTRUCTOR";};
    ~TrackRepo(){qDebug()<<"TrackRepo DESTRUCTOR";};
    Track getTrack(int id);
    Track getTrack(const std::string &uuid);
    std::vector<Track> getTracks();
    std::vector<Track> getTracksByName(const std::string name_tr);
    std::vector<Track> getTracksDateOrder();    
    std::vector<Track> getFilteredTracks(Genre g);


private:
    std::shared_ptr<AccessorDB> db;
};

#endif // TRACKREPO_H
