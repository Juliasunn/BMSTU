#ifndef REPOCREATOR_H
#define REPOCREATOR_H
#include "userrepo.h"
#include "trackrepo.h"
#include "listenrepo.h"
#include "usertrackrepo.h"
#include "DAL_global.h"



class DAL_EXPORT RepoCreator
{
private:
    std::shared_ptr<UserRepo> uRepo;
    TrackRepo *tRepo;
    std::shared_ptr<ListenRepo> lRepo;
    std::shared_ptr<UserTrackRepo> utRepo;

    std::shared_ptr<AccessorDB> db;
    void createDBAccessor();
    RepoCreator();
public:
    static RepoCreator *getCretor(){
        static RepoCreator *instance = new RepoCreator();
        return instance;
        ;
    }
    RepoCreator(const RepoCreator &) = delete;
    RepoCreator(const RepoCreator &&) = delete;
    std::shared_ptr<UserRepo> getUserRepo();
    TrackRepo *getTrackRepo();
    std::shared_ptr<ListenRepo> getListenRepo();
    std::shared_ptr<UserTrackRepo> getUserTrackRepo();
};

#endif // REPOCREATOR_H
