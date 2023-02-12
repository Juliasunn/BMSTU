#include "include/user.h"


int User::getId() const
{
    return id;
}

int User::getPriveledges_level() const
{
    return priveledges_level;
}

void User::setPriveledges_level(int value)
{
    priveledges_level = value;
}

std::string User::getLogin() const
{
    return login;
}

std::string User::getPassword() const
{
    return password;
}

void User::setId(int value)
{
    id = value;
}

void User::setLogin(const std::string &value)
{
    login = value;
}

void User::setPassword(const std::string &value)
{
    password = value;
}


