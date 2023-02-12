#ifndef DTOCONVERTER_H
#define DTOCONVERTER_H
#include "../Resources/userresource.h"
#include "../Resources/favoritesresource.h"
#include "../Resources/trakresource.h"
#include "dtouser.h"
#include "dtotrak.h"
#include "dtotraklist.h"


class DTOTrakConverter
{
public:
    static DTOTrak createDTOTrak(const TrakResource &res);

};

class DTOTrakListConverter
{
public:
    static DTOTrakList createDTOTrakList(const FavoritesResource &res);
    static DTOTrakList createDTOTrakList(const std::vector<TrakResource> &res_vec);

};

class DTOUserConverter
{
private:
    std::map<int, std::string> userPrivMap = {
        {1, "basic user"},
        {2, "administrator"}
    };
public:
    DTOAuthorizationData createDTOAuthData(const UserResource &res) const;
    DTOAccountData createDTOAccountData(const UserResource &res) const;

    UserResource createUserResource(const DTOAuthorizationData &dto) const;
    UserResource createUserResource(const DTOAccountData &dto) const;
};

#endif // DTOCONVERTER_H
