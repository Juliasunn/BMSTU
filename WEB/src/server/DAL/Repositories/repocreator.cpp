#include "include/repocreator.h"




void RepoCreator::createDBAccessor()
{
    AccessorDBCreator &creator = AccessorDBCreator::getCreator();
    db = creator.get_accessor(DB_CNF_PATH, APP_CNF_PATH);
}

RepoCreator::RepoCreator()
{qDebug()<<"Repo Creator constuctor";
    this->createDBAccessor();
    utRepo = std::shared_ptr<UserTrackRepo>(new UserTrackRepo(db));
    tRepo = new TrackRepo(db);
    lRepo = std::shared_ptr<ListenRepo>(new ListenRepo(db));
}

std::shared_ptr<UserTrackRepo> RepoCreator::getUserTrackRepo()
{
    if (utRepo.get()!=nullptr)
        return utRepo;
    if (!db)
        createDBAccessor();
    utRepo = std::shared_ptr<UserTrackRepo>(new UserTrackRepo(db));

    return utRepo;
}

std::shared_ptr<UserRepo> RepoCreator::getUserRepo()
{
    if (uRepo.get()!=nullptr)
        return uRepo;
    if (!db)
        createDBAccessor();
    uRepo = std::shared_ptr<UserRepo>(new UserRepo(db));
    return uRepo;
}

TrackRepo *RepoCreator::getTrackRepo()
{
   // return nullptr;
    if (tRepo!=nullptr)
        return tRepo;
    if (!db)
        createDBAccessor();
    tRepo = new TrackRepo(db);
    return tRepo;
}

std::shared_ptr<ListenRepo> RepoCreator::getListenRepo()
{
    if (lRepo.get()!=nullptr)
        return lRepo;
    if (!db)
        createDBAccessor();
    lRepo = std::shared_ptr<ListenRepo>(new ListenRepo(db));
    return lRepo;
}
