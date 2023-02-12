#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <logger.h>
#include "exceptionsdb.h"
#include "../BL/Tools/tools.h"

class ServerConfig
{
private:
    std::string serverName;
    std::map<std::string, std::string> responseHeaders;
public:
    ServerConfig()=default;
    ServerConfig(const std::string &filename);
    std::map<std::string, std::string> getResponseHeaders() const;
    std::string getServerName() const;
};

#endif // SERVERCONFIG_H
