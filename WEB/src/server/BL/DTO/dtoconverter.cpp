#include "dtoconverter.h"
#include <QDebug>

DTOAuthorizationData DTOUserConverter::createDTOAuthData(const UserResource &res) const
{
    DTOAuthorizationData dto;

    dto.setLogin(res.getLogin());
    dto.setPassword(res.getPassword());

    return dto;

}

DTOAccountData DTOUserConverter::createDTOAccountData(const UserResource &res) const
{
    DTOAccountData dto;

    int priv_level = res.getPriveledges_level();

    auto tmp = userPrivMap;
    std::string priv_name = tmp[priv_level];

    dto.setLogin(res.getLogin());
    dto.setPriveledges(priv_name);

    return dto;
}

UserResource DTOUserConverter::createUserResource(const DTOAuthorizationData &dto) const
{
    UserResource res;

    res.setLogin(dto.getLogin());
    res.setPassword(dto.getPassword());
    return res;
}

UserResource DTOUserConverter::createUserResource(const DTOAccountData &dto) const
{
    UserResource res;
    res.setLogin(dto.getLogin());
    res.setPriveledges_level(Tools::get_key<int>(userPrivMap, dto.getPriveledges()));
    return res;
}

DTOTrak DTOTrakConverter::createDTOTrak(const TrakResource &res)
{
    DTOTrak dto;
    dto.setName(res.getName());
    dto.setArtist(res.getArtist());
    dto.setGenre(res.getGenre());
    dto.setFileUrl(res.getFileUrl());
    dto.setGuid(res.getGuid());
    return dto;
}

DTOTrakList DTOTrakListConverter::createDTOTrakList(const FavoritesResource &res)
{
    qDebug() << "DTOConverter::createDTOTrakList(const FavoritesResource";
    DTOTrakList dto;
    std::vector<DTOTrak> res_vec;

    return createDTOTrakList(res.getFavorites());
}

DTOTrakList DTOTrakListConverter::createDTOTrakList(const std::vector<TrakResource> &res_vec)
{
    qDebug() << "DTOConverter::createDTOTrakList(const std::vector<TrakResource>";
    DTOTrakList dto;
    std::vector<DTOTrak> vec;
    for (auto t_res : res_vec) {
        vec.push_back(DTOTrakConverter::createDTOTrak(t_res));

    }
    dto.setVec(vec);
   // qDebug() << "ok";
    return dto;
}
