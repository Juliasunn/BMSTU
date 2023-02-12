#ifndef TRAKRESOURCE_H
#define TRAKRESOURCE_H
#include <DAL_global.h>
#include <track.h>


class TrakResource
{
private:
    //int id;
    std::string name;
    std::string genre;
    std::string artist;
    std::string fileUrl;
    std::string guid;
public:
    TrakResource()=default;
    TrakResource(const std::string &guid_, const std::string &name_, const std::string &genre_,
                 const std::string &artist_, const std::string &fileUrl_):
        guid(guid_), name(name_), genre(genre_), artist(artist_), fileUrl(fileUrl_)
    {};

    std::string getName() const;
    std::string getGenre() const;
    std::string getArtist() const;
    std::string getFileUrl() const;
    void setFileUrl(const std::string &value);

    std::string getGuid() const;
    void setGuid(const std::string &value);
};

#endif // TRAKRESOURCE_H
