#ifndef DTOTRAK_H
#define DTOTRAK_H
#include <string_view>
#include <string>
#include </home/julia/boost/boost/json.hpp>
#include "../Tools/tools.h"
#include "../headers/req_exceptions.h"

class DTOTrak
{
private:
    std::string name;
    std::string genre;
    std::string artist;
    std::string fileUrl;
    std::string guid;
public:
    DTOTrak()=default;

    boost::json::value getJson() const;
    void fromJson(const boost::json::value &val);

    std::string getName() const;
    void setName(const std::string &value);
    std::string getGenre() const;
    void setGenre(const std::string &value);
    std::string getArtist() const;
    void setArtist(const std::string &value);
    std::string getFileUrl() const;
    void setFileUrl(const std::string &value);
    std::string getGuid() const;
    void setGuid(const std::string &value);
};

#endif // DTOTRAK_H
