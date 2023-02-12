#include "favoritesresource.h"


std::vector<TrakResource> FavoritesResource::getFavorites() const
{
    return favorites;
}

void FavoritesResource::setFavorites(const std::vector<TrakResource> &value)
{
    favorites = value;
}
