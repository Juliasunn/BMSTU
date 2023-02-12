#ifndef ACCESSORDB_H
#define ACCESSORDB_H
#include <memory>
#include <stdio.h>
#include "querycreator.h"
#include "connector.h"
#include "user.h"
#include "track.h"
#include <logger.h>
#include "dalconfig.h"
#include "paramchecker.h"

class AccessorDB
{
private:
    std::shared_ptr<Connector> con;
    std::shared_ptr<QueryCreator> qCreator;
    std::shared_ptr<ParamChecker> pChecker;
public:
    AccessorDB(std::shared_ptr<Connector> c, std::shared_ptr<QueryCreator> qCr,
               std::shared_ptr<ParamChecker> pCh):con(c), qCreator(qCr), pChecker(pCh)
    {con->openConnection();};

    void setCon(const std::shared_ptr<Connector> &value);
    void setQCreator(const std::shared_ptr<QueryCreator> &value);

    User getUser(int id);
    User getUser(const std::string &login, const std::string &password);
    bool addUser(const std::string &login, const std::string &password);
    bool checkUserExists(const std::string &login, const std::string &password);
    bool changeUserPassword(int id_user, const std::string &new_password);
    bool checkLoginFree(const std::string &login);

    std::vector<Track> getTracks();
    Track getTrack(int id);
    Track getTrack(const std::string &uuid);
    std::vector<Track> getTracks(const std::string name_tr);
    std::vector<Track> getSortedTracks(Column sort_field);
    std::vector<Track> getFilteredTracks(Genre g);

    std::vector<Listening> getListeningsTrack(int id_track);
    int counListenings(int id_track);
    std::vector<Listening> getListeningsUser(int id_user);
    bool addListening(int id_user, int id_track);

    std::vector<Track> getUserTracks(int id_user);
    bool deleteUserTrack(int id_track, int id_user);
    Track getUserTrack(const std::string &uuid, int id_user);
    bool addTrack(int id_track, int id_user);
    bool isTrackAdded(int id_track, int id_user);
};

class AccessorDBCreator
{
public:
    static AccessorDBCreator &getCreator(){static AccessorDBCreator instance; return instance;};
    std::shared_ptr<AccessorDB> get_accessor(std::string connect_cnf, std::string app_cnf);
private:
    AccessorDBCreator(){db=nullptr;};
    AccessorDBCreator(const AccessorDBCreator &)=delete;
    AccessorDBCreator &operator=(AccessorDBCreator &)=delete;
    std::shared_ptr<AccessorDB> db;
};


#endif // ACCESSORDB_H
