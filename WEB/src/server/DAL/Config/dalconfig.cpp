#include "include/dalconfig.h"

int DalConfig::getSubd() const
{
    return subd;
}

int DalConfig::getDbFramework() const
{
    return dbFramework;
}

std::shared_ptr<ParamChecker> DalConfig::getChecker() const
{
    return checker;
}

DalConfig::DalConfig(std::string filename)
{
    qDebug()<< "Dal config called";
    std::ifstream conFile;
    conFile.open(filename);

    Logger::InfoMsg("DalConfig opening "+filename);
    if (!conFile.is_open())
    {
        Logger::ErrorMsg("Could not open "+filename);
        throw confile_exception();
    }

    try
    {
        conFile >> subd >> dbFramework;
        Logger::InfoMsg(std::to_string(subd) + " " +std::to_string(dbFramework));

    }

    catch (...)
    {
        conFile.close();
        throw confile_exception();
    }


    std::vector<char> validSymbols;

    char symb;
    while (conFile >> symb){
        validSymbols.push_back(symb);
    }
    conFile.close();

    checker = std::shared_ptr<ParamChecker>(new ParamChecker(validSymbols));
}





