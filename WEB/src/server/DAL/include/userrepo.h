#ifndef USERREPO_H
#define USERREPO_H
#include "accessordb.h"
#include "DAL_global.h"
class DAL_EXPORT UserRepo
{
public:
    UserRepo(std::shared_ptr<AccessorDB> db_):db(db_){};
    User getUser(int id);
    User getUser(const std::string &login, const std::string &password);
    bool addUser(const std::string &login, const std::string &password);

    bool checkLoginFree(const std::string &login);
    bool checkUserExists(const std::string &login, const std::string &password);
    bool changeUserPassword(int id_user, const std::string &new_password);
private:
    std::shared_ptr<AccessorDB> db;
};

#endif // USERREPO_H
