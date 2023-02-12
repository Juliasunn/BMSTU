#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#define LOGFILENAME "../logfile.txt"

enum LogLevel
{
    DEBUG,
    INFO,
    ERR,
};

class Logger
{
private:
    static void write(const LogLevel lvl, const std::string &msg);
public:
    Logger()=delete;

    static void DebugMsg(const std::string &msg);
    static void InfoMsg(const std::string &msg);
    static void ErrorMsg(const std::string &msg);
};
#endif // LOGGER_H
