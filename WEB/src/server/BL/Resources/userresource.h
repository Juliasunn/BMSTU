#ifndef USERRESOURCE_H
#define USERRESOURCE_H
#include <DAL_global.h>
#include <user.h>
#include <map>

#include <string_view>
#include <string>
#include </home/julia/boost/boost/json.hpp>



class UserResource
{
private:
    std::string login;
    std::string password;
    int priveledges_level;
public:
    UserResource()=default;
    UserResource(const std::string &login_, const std::string &password_, int priveledges_level_=1): login(login_),
        password(password_), priveledges_level(priveledges_level_){};

    std::string getLogin() const;
    std::string getPassword() const;
    int getPriveledges_level() const;
    void setPriveledges_level(int value);
    void setLogin(const std::string &value);
    void setPassword(const std::string &value);
};



#endif // USERRESOURCE_H
