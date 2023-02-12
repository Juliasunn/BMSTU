#include "dtotrak.h"

std::string DTOTrak::getName() const
{
    return name;
}

void DTOTrak::setName(const std::string &value)
{
    name = value;
}

std::string DTOTrak::getGenre() const
{
    return genre;
}

void DTOTrak::setGenre(const std::string &value)
{
    genre = value;
}

std::string DTOTrak::getArtist() const
{
    return artist;
}

void DTOTrak::setArtist(const std::string &value)
{
    artist = value;
}

std::string DTOTrak::getFileUrl() const
{
    return fileUrl;
}

void DTOTrak::setFileUrl(const std::string &value)
{
    fileUrl = value;
}

std::string DTOTrak::getGuid() const
{
    return guid;
}

void DTOTrak::setGuid(const std::string &value)
{
    guid = value;
}

boost::json::value DTOTrak::getJson() const
{
    boost::json::value val = {
        {"guid", guid},
        {"name", name},
        {"genre", genre},
        {"artist", artist},
        {"fileUrl", fileUrl}

    };
    return val;
}

void DTOTrak::fromJson(const boost::json::value &val)
{
    try{
        name = Tools::extract_string(val.at("name"));
        genre = Tools::extract_string(val.at("genre"));
        artist = Tools::extract_string(val.at("artist"));
    }
    catch (std::exception &e)
    {
        throw invalid_params();
    }
}
