#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#define MAX_PARAM_SIZE 1024
#include </home/julia/boost/boost/beast/core.hpp>
#include </home/julia/boost/boost/beast/http.hpp>
#include </home/julia/boost/boost/asio.hpp>
#include <stdlib.h>
#include <map>
#include <QDebug>
#include <../BL/HTTPServices/userhttpservice.h>
#include <../BL/HTTPServices/trakhttpservice.h>
#include "../BL/Facades/httpfacade.h"
#include "mapper.h"

#include "../BL/Config/serverconfig.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Controller
{
public:
    Controller()=default;
    Controller(const ServerConfig &conf_):conf(conf_){};

    void process_http_request(http::request<http::string_body> r) ;


    http::response<http::string_body> get_response();
    void setConf(const ServerConfig &value);

private:
    ServerConfig conf;
    HTTPFacade facade;
    void create_options_resp();
    void form_http_response(const boost::json::value &result, http::status status_);

    std::map<std::string, std::string> parse_req_params(const std::string &params_str);
    std::map<std::string, std::string> parse_req_headers();

    // The request message.
    http::request<http::string_body> request_;

    // The response message.
    http::response<http::string_body> response_;
};

#endif // REQUESTHANDLER_H
