#include "userhttpservice.h"
#include <repocreator.h>
#include "../Tools/tools.h"
#include <exceptionsdb.h>

boost::json::value UserHTTPService::processLogUser(std::string body)
{
    qDebug() << "user/login called";
    boost::json::value token;
    Mapper p;

    boost::json::value userJson = boost::json::parse(body);
    UserResource u =  p.userFromJson(userJson);
    std::string login = u.getLogin().c_str();
    std::string password =u.getPassword().c_str();

    try {
        if (uRepo->checkUserExists(login, password)){
           token = auth_service_->generate_jwt((uRepo->getUser(login,
                                         password)).getId());
        }
        else {
            throw auth_exception();
        }
    }
    catch (forbidden_symb_exception &e) {
         throw invalid_params();
    }
    return token;
}

boost::json::value UserHTTPService::processReqUser(std::string body)
{
    qDebug() << "user/registration called";
    Mapper p;
    boost::json::value token = {};
    boost::json::value userJson = boost::json::parse(body);
    UserResource u =  p.userFromJson(userJson);

    try {
        if (uRepo->checkLoginFree(u.getLogin()) == true){
            int ret = uRepo->addUser(u.getLogin(), u.getPassword());
            if (ret){
                token = auth_service_->generate_jwt(uRepo->getUser(u.getLogin(),
                                                         u.getPassword()).getId());
            }
        }
        else {
            throw req_conflict_exception();
        }
    }
    catch (forbidden_symb_exception &e) {
         throw invalid_params();
    }
    return token;
}

boost::json::value UserHTTPService::processGetUser(const std::string &auth_field)
{
    Mapper p;

   int id =  auth_service_->get_id(auth_field);
   if (id == -1)
       throw auth_exception();
   UserResource u = UserResourceConverter::createUserResource(uRepo->getUser(id));
   return p.userToJson(u);
}

bool UserHTTPService::processEditUser(std::string body, const std::string &auth_field)
{
   bool result;
   int id =  auth_service_->get_id(auth_field);
   if (id == -1) {
       throw auth_exception();
   }
   boost::json::value passwordJson = boost::json::parse(body);
   Mapper p;
   std::string new_password = p.extract_string(passwordJson.at("password"));

   if (new_password == EMPTY_STRING) {
       throw invalid_params();
   }
   try {
       result = uRepo->changeUserPassword(id, new_password);
   }
   catch (forbidden_symb_exception &e) {
        throw invalid_params();
   }
   return result;
}

bool UserHTTPService::checkPriveledgesForAction(const std::string &auth_field, int action_priv_lvl)
{
    int id =  auth_service_->get_id(auth_field);
    if (id == -1) {
        throw auth_exception();
    }

    UserResource res = UserResourceConverter::createUserResource(uRepo->getUser(id));
    return res.getPriveledges_level() >= action_priv_lvl;
}

UserHTTPService::UserHTTPService()
{
    auth_service_ = AuthService::get_service();
    uRepo = (RepoCreator::getCretor())->getUserRepo();
}
