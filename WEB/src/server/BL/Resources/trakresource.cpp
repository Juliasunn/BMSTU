#include "trakresource.h"

void TrakResource::setFileUrl(const std::string &value)
{
    fileUrl = value;
}


std::string TrakResource::getGuid() const
{
    return guid;
}

void TrakResource::setGuid(const std::string &value)
{
    guid = value;
}

std::string TrakResource::getName() const
{
    return name;
}

std::string TrakResource::getGenre() const
{
    return genre;
}

std::string TrakResource::getArtist() const
{
    return artist;
}

std::string TrakResource::getFileUrl() const
{
    return fileUrl;
}

