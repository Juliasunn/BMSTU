#ifndef RESCONVERTER_H
#define RESCONVERTER_H
#include "trakresource.h"
#include "userresource.h"
#include "favoritesresource.h"

class TrakResourceConverter
{
public:
    TrakResourceConverter()=delete;
    static TrakResource createTrakResource(const Track &db);
};

class FavoritesResourceConverter
{
public:
    FavoritesResourceConverter()=delete;
    static FavoritesResource createFavoritesResource(const std::vector<Track> &db_list);
};

class UserResourceConverter
{
public:
    UserResourceConverter()=delete;
    static UserResource createUserResource(const User &db);
};



#endif // RESCONVERTER_H
