#include "authservice.h"


boost::json::value AuthService::generate_jwt(int id)
{
    boost::json::value header, payload;
    header = {
        {"alg","HS256"},
        {"typ", "JWT"}
    };
    payload = { "userId", id }; //claim

    std::string data = base64_encode(serialize(header)) +
            '.' + base64_encode(serialize(payload));

    unsigned char buffer[64 + SHA256_DIGEST_LENGTH];

    hmac_sha256((const unsigned char*)(data.c_str()), data.size(),
            (const unsigned char*)(secret_key.c_str()), secret_key.size(), buffer);

    std::string signature = base64_encode(std::string((char *)(buffer)));

    std::string token = data + '.' + signature;

    id_token_map[id] = token; //replace or add
    boost::json::value tokenJson = { {"Token", token}};

    return tokenJson;
}

int AuthService::get_id(const std::string &auth_field) const
{
    qDebug() << "AuthService::auth field = " << auth_field.c_str();
    int u_id;
    int pos = auth_field.find(' ');
    if (pos == -1) {
         throw auth_exception();//wrong format of auth field string
    }

    std::string auth_type = auth_field.substr(0, pos);
    if (auth_type !="Bearer") {
         throw auth_exception();//wrong format of auth field string
    }

    std::string jwt_token = auth_field.substr(pos+1, auth_field.size());
    qDebug() << "token = " << jwt_token.c_str();
    for (const auto& [id, token] : id_token_map) {
        qDebug() << "map token " << token.c_str();
       if (token == jwt_token) {
           qDebug() << "AuthService::get_id = " << id;
           return id;         
       }

   }

    return -1; //no user with this token;
}


