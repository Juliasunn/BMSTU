#include "include/track.h"

int Track::getNumListenings() const
{
    return numListenings;
}

void Track::setNumListenings(int value)
{
    numListenings = value;
}

std::string Track::getGenre() const
{
    return genre;
}

std::string Track::getUuid() const
{
    return uuid;
}

void Track::setUuid(const std::string &value)
{
    uuid = value;
}

int Track::getId() const
{
    return id;
}

std::string Track::getName() const
{
    return name;
}

std::string Track::getArtist() const
{
    return artist;
}

std::string Track::getFile_name() const
{
    return file_name;
}


