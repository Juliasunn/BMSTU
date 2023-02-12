#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdlib.h>
#include <string.h>

class Targets
{
public:
    static std::string traks_path(){return "/traks";};
    static std::string trak_path(){return "/traks/";};

    static std::string user_login_path(){return "/users/login";};
    static std::string user_reg_path(){return "/users/registration";};
    static std::string user_get_path(){return "/account";};
    static std::string user_edit_path(){return "/account";};

    static std::string favs_path(){return "/favorites";};
    static std::string fav_path(){return "/favorites/";};
    static std::string fav_add_path(){return "/favorites/";};
    static std::string fav_delete_path(){return "/favorites/";};

};






#endif // CONSTANTS_H
