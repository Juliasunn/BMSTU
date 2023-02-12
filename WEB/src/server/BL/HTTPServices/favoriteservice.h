#ifndef FavoriteService_H
#define FavoriteService_H
#include "authservice.h"
#include <userrepo.h>
#include <usertrackrepo.h>
#include <track.h>
#include <stdlib.h>
#include <memory>
#include "../HTTP/mapper.h"
#include <repocreator.h>
#include "../Resources/favoritesresource.h"
#include "../Resources/resconverter.h"

class FavoriteService
{
public:
    boost::json::array processGetFavs(const std::string &auth_field);
    boost::json::value processGetFav(const std::string &guid, const std::string &auth_field);
    bool processPostFav(const std::string &guid, const std::string &auth_field);
    bool processDeleteFav(const std::string &guid, const std::string &auth_field);

    FavoriteService();
private:
    std::shared_ptr<UserTrackRepo> fRepo;
    std::shared_ptr<TrackRepo> tRepo;
    std::shared_ptr<AuthService> auth_service_;
    //ResConverter c;
    Mapper p;
};

#endif // FavoriteService_H
