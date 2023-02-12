#ifndef USERTRACKREPO_H
#define USERTRACKREPO_H
#include "accessordb.h"
 #include "DAL_global.h"
 
class DAL_EXPORT UserTrackRepo
{
public:
   UserTrackRepo(std::shared_ptr<AccessorDB> db_):db(db_){};

   std::vector<Track> getUserTracks(int u_id);
   std::vector<Track> getUserTracks(User us);
   Track getUserTrack(const std::string &guid, int u_id);

   void deleteTrack(int t_id, int u_id);
   void deleteTrack(const std::string &t_uuid, int u_id);
   void deleteTrack(Track track_, User us);

   void addTrack(int t_id, int u_id);
   void addTrack(const std::string &t_uuid, int u_id);
   void addTrack(Track track_, User us);
   bool isTrackAdded(Track track_, User us);
private:
    std::shared_ptr<AccessorDB> db;
};

#endif // USERTRACKREPO_H
