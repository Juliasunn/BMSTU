#include "serverconfig.h"

std::map<std::string, std::string> ServerConfig::getResponseHeaders() const
{
    return responseHeaders;
}

std::string ServerConfig::getServerName() const
{
    return serverName;
}

ServerConfig::ServerConfig(const std::string &filename)
{
    qDebug()<< "ServerConfig called";
    std::ifstream conFile;
    conFile.open(filename);

        Logger::InfoMsg("ServerConfig opening "+filename);
        if (!conFile.is_open())
        {
            Logger::ErrorMsg("Could not open "+filename);
            throw confile_exception();
        }

        try
        {
            getline(conFile, serverName);
            qDebug() << serverName.c_str();

            std::vector<std::string> confStrings;
            std::string s;
            while(getline(conFile, s)){ // пока не достигнут конец файла класть очередную строку в переменную (s)
                confStrings.push_back(s);
            }
            conFile.close();

            for (auto str : confStrings){
                qDebug() << str.c_str();
                std::vector<std::string> splitted = Tools::split_string(str,':');
                responseHeaders.insert(std::make_pair<std::string>(std::string(splitted[0]), std::string(splitted[1])));
            }
        }
        catch (...)
        {
            throw confile_exception();
        }
}
