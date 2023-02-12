#include "mapper.h"
#include <QDebug>
#include "../BL/headers/req_exceptions.h"

std::string Mapper::extract_string(const boost::json::value &val) const
{
    return Tools::extract_string(val);
}

boost::json::value Mapper::trackToJson(const TrakResource &res) const
{
    DTOTrak dto = c.createDTOTrak(res);
    return dto.getJson();
}

boost::json::array Mapper::tracksToJsonArray(std::vector<TrakResource> &res_vec) const
{
    DTOTrakList dto = c.createDTOTrakList(res_vec);
    return dto.getJson();
}

UserResource Mapper::userFromJson(const boost::json::value &userJson) const
{
    DTOAuthorizationData dto;
    dto.fromJson(userJson);
    return c.createUserResource(dto);
}

boost::json::value Mapper::userToJson(const UserResource &u) const
{
    DTOConverter c;
    DTOAccountData dto = c.createDTOAccountData(u);
    return dto.getJson();
}

boost::json::array Mapper::favoritesToJsonArray(const FavoritesResource &favorites) const
{
    DTOTrakList dto = c.createDTOTrakList(favorites);
    return dto.getJson();
}
