#ifndef DTOUSER_H
#define DTOUSER_H

#include <string_view>
#include <string>
#include </home/julia/boost/boost/json.hpp>
#include "../Tools/tools.h"
#include "../headers/req_exceptions.h"

class DTOAuthorizationData
{
private:
    std::string login;
    std::string password;
public:
    DTOAuthorizationData()=default;

    boost::json::value getJson() const;
    void fromJson(const boost::json::value &val);

    void setLogin(const std::string &value);
    void setPassword(const std::string &value);
    std::string getLogin() const;
    std::string getPassword() const;
};

class DTOAccountData
{
private:
    std::string login;
    std::string priveledges;
public:
    DTOAccountData()=default;

    boost::json::value getJson() const;
    void fromJson(const boost::json::value &val);

    void setLogin(const std::string &value);
    void setPriveledges(const std::string &value);
    std::string getLogin() const;
    std::string getPriveledges() const;
};

#endif // DTOUSER_H
