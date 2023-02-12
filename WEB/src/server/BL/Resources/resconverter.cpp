#include "resconverter.h"

TrakResource TrakResourceConverter::createTrakResource(const Track &db)
{
   TrakResource res(db.getUuid(), db.getName(), db.getGenre(), db.getArtist(), db.getFile_name());
   return res;
}

UserResource UserResourceConverter::createUserResource(const User &db)
{
    UserResource res(db.getLogin(), db.getPassword(), db.getPriveledges_level());
    return res;
}

FavoritesResource FavoritesResourceConverter::createFavoritesResource(const std::vector<Track> &db_list)
{
    FavoritesResource res;
    std::vector<TrakResource> res_list;

        for (auto db : db_list){
            res_list.push_back(TrakResourceConverter::createTrakResource(db));
        }
    res.setFavorites(res_list);

    return res;
}
