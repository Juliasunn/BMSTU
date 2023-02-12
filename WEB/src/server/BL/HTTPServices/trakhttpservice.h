#ifndef TRAKHTTPSERVICE_H
#define TRAKHTTPSERVICE_H
#include "../HTTP/mapper.h"
#include <boost/beast.hpp>
#include  <boost/beast/http.hpp>
#include <DAL_global.h>
#include <trackrepo.h>
#include  <memory>
#include <repocreator.h>
#include <boost/beast/http/string_body.hpp>
#include "authservice.h"
#include "../Resources/resconverter.h"

namespace beast = boost::beast;
namespace http = boost::beast::http;

//параметры, тело
class TrakHTTPService
{

public:
    boost::json::array ProcessGetTraks(const std::map<std::string, std::string> &query_params,
                                       const std::string &auth_field);
    boost::json::value ProcessGetTrak(const std::string &guid, const std::string &auth_field);

    TrakHTTPService();
private:
    std::vector<TrakResource> toTraksResource(const std::vector<Track> &trList);
    std::shared_ptr<AuthService> auth_service_;
    TrackRepo *tRepo;
    //ResConverter c;
    Mapper p;
};

#endif // TRAKHTTPSERVICE_H
