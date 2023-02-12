#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H
#include <stdlib.h>
#include <map>
#include <string>
#include "jwt_encrypt_alg.h"
#include <boost/json.hpp>
#include <memory>
#include "../HTTP/mapper.h"
#include "../headers/req_exceptions.h"

class AuthService
{
public:
    static std::shared_ptr<AuthService> get_service(){
       static std::shared_ptr<AuthService> instance = std::shared_ptr<AuthService>(new  AuthService());
       return instance;
    }

    boost::json::value generate_jwt(int id); //!generates and adds/replaces this id in map with generated jwt
    int get_id(const std::string &auth_field) const; //!-1 if does not exist
    ~AuthService()=default;
private:
    AuthService()=default;
    std::string secret_key = std::string("cAtwa1kkEy");
    std::map<int, std::string> id_token_map;
};

#endif // AUTHSERVICE_H
