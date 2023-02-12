#include "controller.h"

#include <iostream>
#include <QDebug>
#include <cstring>
#include </home/julia/boost/boost/json.hpp>
#include <trackrepo.h>
#include <repocreator.h>
#include "../BL/Tools/tools.h"


void Controller::process_http_request(http::request<http::string_body> r)
{
    this->request_ = r;
    response_={};

    qDebug() << "process_http_request called";
    response_.version(request_.version());
    response_.keep_alive(request_.keep_alive());
    response_.set(http::field::server, conf.getServerName());
    response_.set("Access-Control-Allow-Origin", "*");

    switch(request_.method())
    {
    case(http::verb::unknown):
        response_.result(http::status::bad_request);
        qDebug() << "UNKNOWN request";
        break;
     case(http::verb::options):
        create_options_resp();
        qDebug() << "OPTIONS request";
        break;
    default:
        qDebug() << "DEFAULT request";
        std::string request_url = request_.target();
        std::map<std::string, std::string> query_params, header_map;

        header_map = parse_req_headers();

        std::string auth_header = Tools::get_string<std::string>(header_map, "Authorization");

        std::vector<std::string> url_splited = Tools::split_string(request_url,'?');
        std::string request_target = url_splited[0];

        if (url_splited.size()>=2){
            query_params = parse_req_params(url_splited[1]);
        }
        std::string action = (std::string(to_string(request_.method()))).append(request_target);
        boost::json::value result;
        http::status status_ = facade.processRequest(action, query_params, request_.body(), auth_header, result);
        this->form_http_response(result, status_);
        break;
    }
}

void Controller::form_http_response(const boost::json::value &result, http::status status_)
{
    qDebug()<< "form_http_response()";
    response_.result(status_);
    if (status_ == http::status::ok && serialize(result) != "null")
    {
        response_.set(http::field::content_type, "application/json");
        response_.body() = serialize(result);
        response_.prepare_payload();
    }
    std::cout << "response" << response_;
}


http::response<http::string_body> Controller::get_response()
{
    return response_;
}

void Controller::setConf(const ServerConfig &value)
{
    conf = value;
}

void Controller::create_options_resp()
{
    response_ = {};
    response_.version(request_.version());
    response_.set(http::field::server, conf.getServerName());
    response_.keep_alive(request_.keep_alive());
    response_.result(http::status::ok);

    for (std::pair<std::string, std::string> header: conf.getResponseHeaders()){
        response_.set(header.first, header.second);
    }
}

std::map<std::string, std::string> Controller::parse_req_params(const std::string &params_str)
{
    std::map<std::string, std::string> query_params;

    std::vector<std::string> params= Tools::split_string(params_str,'&');
    for (auto param : params){
        std::vector<std::string> splitted = Tools::split_string(param,'=');
        query_params.insert(std::make_pair<std::string>(std::string(splitted[0]), std::string(splitted[1])));
    }
    return query_params;
}

std::map<std::string, std::string> Controller::parse_req_headers()
{
    std::map<std::string, std::string> header_map;
    for (auto& h : request_.base()) {
        header_map.insert(std::make_pair<std::string>(std::string(h.name_string()), std::string(h.value())));
        //std::cout << "Field: " << h.name_string() << ", Value: " << h.value() << "\n";
    }
    return header_map;
}
