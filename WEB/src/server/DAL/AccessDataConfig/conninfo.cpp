#include "include/conninfo.h"

std::string ConnInfo::getNameDB() const
{
    return nameDB;
}

void ConnInfo::setNameDB(const std::string &value)
{
    nameDB = value;
}

std::string ConnInfo::getNameUser() const
{
    return nameUser;
}

void ConnInfo::setNameUser(const std::string &value)
{
    nameUser = value;
}

std::string ConnInfo::getPassword() const
{
    return password;
}

std::string ConnInfo::getPort() const
{
    return port;
}

void ConnInfo::setPort(const std::string &value)
{
    port = value;
}

std::string ConnInfo::getHost() const
{
    return host;
}

void ConnInfo::setHost(const std::string &value)
{
    host = value;
}



ConnInfo::ConnInfo(std::string filename)
{
    std::ifstream conFile;
    conFile.open(filename);
    if (!conFile.is_open())
    {
        Logger::ErrorMsg("Could not open connection config file "+filename);
        throw confile_exception();
    }
    Logger::ErrorMsg("Open connection config file "+filename);
    try
    {
        conFile >> nameDB >> port >> host >> nameUser >> password;
        Logger::InfoMsg(nameDB + " "+port + " " + host + " " + nameUser + " " + password);
        conFile.close();
    }
    catch (...)
    {
        throw confile_exception();
    }
}
