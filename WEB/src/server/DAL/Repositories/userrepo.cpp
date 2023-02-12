#include "include/userrepo.h"


User UserRepo::getUser(int id)
{
    User u;
    try {
       u = db->getUser(id);

    } catch (db_exception &e) {
       qDebug() << e.what();
    }
    return u;
}

User UserRepo::getUser(const std::string &login, const std::string &password)
{
    User u;
    try {
       u = db->getUser(login, password);

    } catch (db_exception &e) {
       qDebug() << e.what();
    }
    return u;
}

bool UserRepo::addUser(const std::string &login, const std::string &password)
{
    try {
       db->addUser(login, password);

    } catch (db_exception &e) {
       qDebug() << e.what();
       return false;
    }
    return true;
}

bool UserRepo::checkLoginFree(const std::string &login)
{
    return db->checkLoginFree(login);
}

bool UserRepo::checkUserExists(const std::string &login, const std::string &password)
{
    return db->checkUserExists(login, password);
}

bool UserRepo::changeUserPassword(int id_user, const std::string &new_password)
{
    try {
       db->changeUserPassword(id_user, new_password);

    } catch (db_exception &e) {
       qDebug() << e.what();
       return false;
    }
    return true;
}
