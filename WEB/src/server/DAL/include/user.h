#ifndef USER_H
#define USER_H
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <variant>
#include <vector>
#include "DAL_global.h"

namespace ns_user
{
enum columnPos
    {id_pos,
     login_pos,
     password_pos,
     priveledges_level_pos
    };

struct init_struct
{
    int id;
    std::string login;
    std::string password;
    int priveledges_level;
};
};

class DAL_EXPORT User
{
private:
    int id;
    std::string login;
    std::string password;
    int priveledges_level;
public:
    User()=default;
    User(const ns_user::init_struct st):id(st.id), login(st.login), password(st.password),
         priveledges_level(st.priveledges_level){};


    std::string getLogin() const;
    std::string getPassword() const;
    void setId(int value);
    void setLogin(const std::string &value);
    void setPassword(const std::string &value);

    std::string out(){return std::to_string(id).append(" ").append(login).append(" ")
                .append(password);};
    int getId() const;
    int getPriveledges_level() const;
    void setPriveledges_level(int value);
};

#endif // USER_H
