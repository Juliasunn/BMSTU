#include "httpfacade.h"
//namespace beast = boost::beast;         // from <boost/beast.hpp>
//namespace http = boost::beast::http;
#include <iostream>
#include "../Tools/tools.h"
#include <exception>

http::status HTTPFacade::processRequest(std::string &action,
                            const std::map<std::string, std::string> &query_params,
                            const std::string &body,
                            const std::string &auth_field,
                            boost::json::value &request_result)
{

    http::status status_;
    std::vector<std::string> path_params;
    int req_id = HTTPTools::parse_path(action, path_params,
                              requests_map);
    switch(req_id)
    {
    case (GetTraks):
        status_ = this->processGetTraks(auth_field, query_params, request_result);
        break;
    case(GetTrak):
        status_ = this->processGetTrak(auth_field, path_params, request_result);
        break;
    case(PostTrak):
        status_ = this->processPostTrak(auth_field, body, request_result);
        break;
    case (LogUser):
        qDebug() << "processLogUser";
        status_ = this->processLogUser(body, request_result);
        break;
    case (ReqUser):
        status_ = this->processReqUser(body, request_result);
        break;
    case (GetUser):

        status_ = this->processGetUser(auth_field, request_result);
        break;
    case (PatchUser):
        status_ = this->processEditUser(auth_field, body);
        break;

    case (GetFavs):
        status_ = this->processGetFavs(auth_field, request_result);
        break;
    case (GetFav):
        status_ = this->processGetFav(path_params, auth_field, request_result);
        break;
    case (PostFav):
        status_ = this->processPostFav(path_params, auth_field, request_result);
        break;
    case (DeleteFav):
        status_ = this->processDeleteFav(path_params, auth_field, request_result);
        break;
     default:
        status_ = http::status::bad_request;
        break;
    }
    return status_ ;
}

http::status HTTPFacade::processGetTraks(const std::string &auth_field,
                                         const std::map<std::string, std::string> &query_params,
                                         boost::json::value &request_result)
{
    qDebug() << "HTTPFacade::processGetTraks";
    http::status status_;
    try {
        boost::json::value res = tService->ProcessGetTraks(query_params, auth_field);
        request_result = res;
        status_ = http::status::ok;

    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch (...) {
        status_ = http::status::bad_request;
    }
    return status_;

}

http::status HTTPFacade::processGetTrak(const std::string &auth_field,
                                        const std::vector<std::string> &path_params,
                                        boost::json::value &request_result)
{
    http::status status_;

    if (path_params.size() != 1) {
        return http::status::bad_request;
    }

    std::string guid = path_params[0];

    try {
        boost::json::value res = tService->ProcessGetTrak(guid, auth_field);
        request_result = res;
        status_ = http::status::ok;

    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch(res_not_found_exception &e){
        status_ = http::status::not_found;
    }

    catch (...) {
        status_ = http::status::bad_request;
    }

    return status_;
}

http::status HTTPFacade::processPostTrak(const std::string &auth_field,
                                         const std::string &body,
                                         boost::json::value &request_result)
{
    http::status status_ = http::status::ok;

    if (!(uService->checkPriveledgesForAction(auth_field, actionPriv_map[PostTrak]))) {
        status_ = http::status::forbidden;
    }

    return status_;
}

http::status HTTPFacade::processLogUser(const std::string &body,
                                        boost::json::value &request_result)
{
    http::status status_ = http::status::ok;
    qDebug() << "processLogUser";

    try {
        boost::json::value token = uService->processLogUser(body);

        request_result = token;
        if (serialize(token) == "")
            status_ = http::status::unauthorized;

    }
    catch (...) {
        status_ = http::status::bad_request;
    }
    return status_;
}

http::status HTTPFacade::processReqUser(const std::string &body,
                                        boost::json::value &request_result)
{
    http::status status_ = http::status::ok;

    try {
        boost::json::value token = uService->processReqUser(body);
        request_result = token;
        if (serialize(token) == "")
            status_ = http::status::bad_request;
    }
    catch (req_conflict_exception &e) { //логин при регистрации занят
            status_ = http::status::conflict;
    }
    catch (...) {
        status_ = http::status::bad_request;
    }

    return status_;
}

http::status HTTPFacade::processGetUser(const std::string &auth_field,
                                        boost::json::value &request_result)
{
    http::status status_ = http::status::ok;
    qDebug() << "auth_field = " << auth_field.c_str();

    try {
        boost::json::value user = uService->processGetUser(auth_field);

        request_result = user;
        if (serialize(user) == "")
            status_ = http::status::bad_request;

    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch (...) {
        status_ = http::status::bad_request;
    }

    return status_;
}

http::status HTTPFacade::processEditUser(const std::string &auth_field, const std::string &body)
{
    http::status status_ = http::status::ok;
    qDebug() << "auth_field = " << auth_field.c_str();

    try {
        bool result = uService->processEditUser(body, auth_field);

        if (!result)
            status_ = http::status::bad_request;

    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch (...) {
        status_ = http::status::bad_request;
    }

    return status_;
}

http::status HTTPFacade::processGetFavs(const std::string &auth_field,
                                        boost::json::value &request_result)
{
    http::status status_ = http::status::ok;

    try {
        boost::json::value res = fService->processGetFavs(auth_field);
        request_result = res;
    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch (...) {
    status_ = http::status::bad_request;
    }
    return status_;
}

http::status HTTPFacade::processGetFav(const std::vector<std::string> &path_params,
                                       const std::string &auth_field,
                                       boost::json::value &request_result)
{
    http::status status_;

    if (path_params.size() != 1) {
        return http::status::bad_request;
    }

    std::string guid = path_params[0];

    try {

        boost::json::value res = fService->processGetFav(guid, auth_field);
        request_result = res;
        status_ = http::status::ok;
    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch(res_not_found_exception &e){
        status_ = http::status::not_found;
    }
    catch (...) {
        status_ = http::status::bad_request;
    }
    return status_;
}

http::status HTTPFacade::processPostFav(const std::vector<std::string> &path_params, const std::string &auth_field,
                                        boost::json::value &request_result)
{
    qDebug()<< "HTTPFacade::processPostFav";
    http::status status_;

    if (path_params.size() != 1) {
        return http::status::bad_request;
    }
    std::string guid = path_params[0];

    try {
        boost::json::value res = fService->processPostFav(guid, auth_field);
        request_result = res;
        status_ = http::status::ok;

    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch(res_not_found_exception &e){
        status_ = http::status::not_found;
    }
    catch (...) {
       status_ = http::status::bad_request;
    }
    return status_;
}

http::status HTTPFacade::processDeleteFav(const std::vector<std::string> &path_params, const std::string &auth_field,
                                          boost::json::value &request_result)
{
    http::status status_;
    if (path_params.size() != 1) {
        return http::status::bad_request;
    }

    std::string guid = path_params[0];

    try {
        boost::json::value res = fService->processDeleteFav(guid, auth_field);
        request_result = res;
        status_ = http::status::ok;
    }
    catch(auth_exception &e){
         status_ = http::status::unauthorized;
    }
    catch(res_not_found_exception &e){
        status_ = http::status::not_found;
    }
    catch (...) {
        status_ = http::status::bad_request;
    }
    return status_;
}



HTTPFacade::HTTPFacade()
{
    aService = AuthService::get_service();
    fService = new FavoriteService();
    tService = new TrakHTTPService();
    uService = UserHTTPService::get_service();
    qDebug() << "constructor finished";

}
