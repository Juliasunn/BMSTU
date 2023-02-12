#ifndef LISTENREPO_H
#define LISTENREPO_H
#include "accessordb.h"
 #include "DAL_global.h"
class DAL_EXPORT ListenRepo
{
public:
    ListenRepo(std::shared_ptr<AccessorDB> db_):db(db_){};
    std::vector<Listening> getListeningsTrack(int id_track);
    int counListenings(int id_track);
    std::vector<Listening> getListeningsUser(int id_user);
    bool addListening(int id_user, int id_track);
private:
    std::shared_ptr<AccessorDB> db;
};

#endif // LISTENREPO_H
