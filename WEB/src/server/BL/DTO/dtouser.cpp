#include "dtouser.h"



void DTOAuthorizationData::setLogin(const std::string &value)
{
    login = value;
}

void DTOAuthorizationData::setPassword(const std::string &value)
{
    password = value;
}

std::string DTOAuthorizationData::getLogin() const
{
    return login;
}

std::string DTOAuthorizationData::getPassword() const
{
    return password;
}

boost::json::value DTOAuthorizationData::getJson() const
{

    boost::json::value objJson = {
        {"login", login},
        {"password", password}
    };
    return objJson;
}

void DTOAuthorizationData::fromJson(const boost::json::value &val)
{
    try{
        login = Tools::extract_string(val.at("login"));
        password = Tools::extract_string(val.at("password"));
    }
    catch (std::exception &e)
    {
        throw invalid_params();
    }
}

void DTOAccountData::setLogin(const std::string &value)
{
    login = value;
}

void DTOAccountData::setPriveledges(const std::string &value)
{
    priveledges = value;
}

std::string DTOAccountData::getLogin() const
{
    return login;
}

std::string DTOAccountData::getPriveledges() const
{
    return priveledges;
}

boost::json::value DTOAccountData::getJson() const
{
    boost::json::value objJson = {
        {"login", login},
        {"priveledges", priveledges}
    };
    return objJson;
}

void DTOAccountData::fromJson(const boost::json::value &val)
{
    try{
        login = Tools::extract_string(val.at("login"));
        priveledges = Tools::extract_string(val.at("priveledges"));
    }
    catch (std::exception &e)
    {
        throw invalid_params();
    }
}
