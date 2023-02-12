#ifndef DALCONFIG_H
#define DALCONFIG_H
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <logger.h>
#include "exceptionsdb.h"
#include "paramchecker.h"
#include <memory>

#define POSTGRES_SUBD 0
#define SQLITE_SUBD 1

#define FRAMEWORK_QT 0


class DalConfig
{
private:
    int subd;
    int dbFramework;
    std::shared_ptr<ParamChecker> checker;
public:
    DalConfig(std::string filename);
    int getSubd() const;
    int getDbFramework() const;
    std::shared_ptr<ParamChecker> getChecker() const;
};

#endif // DALCONFIG_H
