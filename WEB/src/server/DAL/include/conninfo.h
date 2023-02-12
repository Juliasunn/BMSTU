#ifndef CONNINFO_H
#define CONNINFO_H
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <logger.h>
#include "exceptionsdb.h"


class ConnInfo
{
private:
    std::string nameDB;
    std::string nameUser;
    std::string password;
    std::string port;
    std::string host;
public:
    ConnInfo(std::string filename);
    std::string getNameDB() const;
    void setNameDB(const std::string &value);
    std::string getNameUser() const;
    void setNameUser(const std::string &value);
    std::string getPassword() const;
    std::string getPort() const;
    void setPort(const std::string &value);
    std::string getHost() const;
    void setHost(const std::string &value);
};

#endif // CONNINFO_H
