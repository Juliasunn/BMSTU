#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H
#include <DAL_global.h>
#include <track.h>
#include <stdio.h>
#include <stdlib.h>
#include <string_view>
#include <string>
#include </home/julia/boost/boost/json.hpp>
#include <userrepo.h>
#include <vector>
#include "../BL/Resources/trakresource.h"
#include "../BL/Resources/userresource.h"
#include "../BL/Resources/favoritesresource.h"
#include "../BL/DTO/dtoconverter.h"

class Mapper
{
private:
    DTOConverter c;
public:
    Mapper()=default;
    std::string extract_string(const boost::json::value &val) const;

    boost::json::value trackToJson(const TrakResource &tr) const;
    boost::json::array tracksToJsonArray(std::vector<TrakResource> &trl) const;
    UserResource userFromJson(const boost::json::value &userJson) const;
    boost::json::value userToJson(const UserResource &u) const;
    boost::json::array favoritesToJsonArray(const FavoritesResource &favorites) const;
};

#endif // OBJECTPARSER_H
