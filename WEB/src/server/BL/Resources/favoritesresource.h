#ifndef FAVORITESRESOURCE_H
#define FAVORITESRESOURCE_H
#include "trakresource.h"
#include <track.h>
#include <stdlib.h>
#include <vector>
#include <string>

class FavoritesResource
{
private:
    std::vector<TrakResource> favorites;
public:
    FavoritesResource()=default;
    std::vector<TrakResource> getFavorites() const;
    void setFavorites(const std::vector<TrakResource> &value);
};

#endif // FAVORITESRESOURCE_H
