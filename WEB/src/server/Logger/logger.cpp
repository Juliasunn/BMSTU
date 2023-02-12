#include "logger.h"
#include <QDebug>


void Logger::write(const LogLevel lvl, const std::string &msg)
{
    std::ofstream logFile;
    logFile.open(LOGFILENAME, std::ofstream::out | std::ofstream::app);
    if (logFile.is_open())
    {
        switch (lvl){
        case(DEBUG):
            logFile << "[DEBUG]:";
            break;
        case(INFO):
            logFile << "[INFO]:";
            break;
        case(ERR):
            logFile << "[ERR]:";
            break;
        default:
            break;
        }
        std::time_t logTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        logFile << std::ctime(&logTime) << msg << std::endl;
        logFile.close();
    }
}


void Logger::DebugMsg(const std::string &msg)
{
    write(DEBUG, msg);

}

void Logger::InfoMsg(const std::string &msg)
{
    write(INFO, msg);

}

void Logger::ErrorMsg(const std::string &msg)
{
    write(ERR, msg);
}
