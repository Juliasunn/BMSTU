#ifndef HTTPFACADE_H
#define HTTPFACADE_H
#include "../HTTPServices/authservice.h"
#include "../HTTPServices/favoriteservice.h"
#include "../HTTPServices/trakhttpservice.h"
#include "../HTTPServices/userhttpservice.h"
#include <stdio.h>
#include <map>
#include <string>
#include <boost/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include "../headers/constants.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;           // from <boost/beast/http.hpp>



class HTTPFacade
{
public:
   HTTPFacade();
   http::status processRequest(std::string &action,
                               const std::map<std::string, std::string> &query_params,
                               const std::string &body,
                               const std::string &auth_field,
                               boost::json::value &request_result);

private:
   http::status processGetTraks(const std::string &auth_field,
                                const std::map<std::string, std::string> &query_params,
                                boost::json::value &request_result);

    http::status processGetTrak(const std::string &auth_field, const std::vector<std::string> &path_params,
                                boost::json::value &request_result);

    http::status processPostTrak(const std::string &auth_field,
                                 const std::string &body,
                                 boost::json::value &request_result);

    http::status processLogUser(const std::string &body,
                                boost::json::value &request_result);
    http::status processReqUser(const std::string &body,
                                boost::json::value &request_result);
    http::status processGetUser(const std::string &auth_field,
                                boost::json::value &request_result);
    http::status processEditUser(const std::string &auth_field,
                                 const std::string &body);

    http::status processGetFavs(const std::string &auth_field, boost::json::value &request_result);
    http::status processGetFav(const std::vector<std::string> &path_params,
                               const std::string &auth_field,
                               boost::json::value &request_result);

    http::status processPostFav(const std::vector<std::string> &path_params,
                                const std::string &auth_field,
                                boost::json::value &request_result);
    http::status processDeleteFav(const std::vector<std::string> &path_params,
                                  const std::string &auth_field,
                                  boost::json::value &request_result);

    enum ReqId{
        Undefined,
        GetTraks,
        GetTrak,
        PostTrak,

        LogUser,
        ReqUser,
        GetUser,
        PatchUser,

        GetFavs,
        GetFav,
        PostFav,
        DeleteFav
    };
    std::map<std::string, int> requests_map = {
    {(std::string((to_string(http::verb::get))).append(Targets::traks_path())), GetTraks},
    {(std::string((to_string(http::verb::get))).append(Targets::trak_path())), GetTrak},
    {(std::string((to_string(http::verb::post))).append(Targets::traks_path())), PostTrak},

    {(std::string((to_string(http::verb::post))).append(Targets::user_reg_path())), ReqUser},
    {(std::string((to_string(http::verb::post))).append(Targets::user_login_path())), LogUser},
    {(std::string((to_string(http::verb::get))).append(Targets::user_get_path())), GetUser},
    {(std::string((to_string(http::verb::patch))).append(Targets::user_edit_path())), PatchUser},

    {(std::string((to_string(http::verb::get))).append(Targets::favs_path())), GetFavs},
    {(std::string((to_string(http::verb::get))).append(Targets::fav_path())), GetFav},
    {(std::string((to_string(http::verb::post))).append(Targets::fav_add_path())), PostFav},
    {(std::string((to_string(http::verb::delete_))).append(Targets::fav_delete_path())), DeleteFav},
    };

    std::map<int, int> actionPriv_map = {
       {PostTrak, 2}
    };
private:
    std::shared_ptr<AuthService> aService;
    FavoriteService *fService;
    TrakHTTPService *tService;
    std::shared_ptr<UserHTTPService> uService;

};

#endif // HTTPFACADE_H
