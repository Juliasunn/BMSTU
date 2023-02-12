#ifndef USERHTTPSERVICE_H
#define USERHTTPSERVICE_H
#include "authservice.h"
#include <userrepo.h>
#include <stdlib.h>
#include <memory>
#include "../HTTP/mapper.h"
#include "../Resources/resconverter.h"

class UserHTTPService
{
public:
    static std::shared_ptr<UserHTTPService> get_service(){
       static std::shared_ptr<UserHTTPService> instance = std::shared_ptr<UserHTTPService>(new  UserHTTPService());
       return instance;
    }

    boost::json::value processLogUser(std::string body); //returns token or empty json if error
    boost::json::value processReqUser(std::string body); //returns token or empty json if error
    boost::json::value processGetUser(const std::string &auth_field); //
    bool processEditUser(std::string body, const std::string &auth_field);

    bool checkPriveledgesForAction(const std::string &auth_field, int action_priv_lvl);


private:
    UserHTTPService();

    std::shared_ptr<AuthService> auth_service_;
    std::shared_ptr<UserRepo> uRepo;
    //ResConverter c;
};

#endif // USERHTTPSERVICE_H
