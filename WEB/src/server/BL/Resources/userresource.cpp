#include "userresource.h"

#include "../Tools/tools.h"
#include "../headers/req_exceptions.h"

std::string UserResource::getPassword() const
{
    return password;
}

int UserResource::getPriveledges_level() const
{
    return priveledges_level;
}

void UserResource::setPriveledges_level(int value)
{
    priveledges_level = value;
}

void UserResource::setLogin(const std::string &value)
{
    login = value;
}

void UserResource::setPassword(const std::string &value)
{
    password = value;
}

std::string UserResource::getLogin() const
{
    return login;
}


