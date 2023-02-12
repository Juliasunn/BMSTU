#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "conninfo.h"
#include "entitycreator.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <vector>
#include "exceptionsdb.h"
#include "dalconfig.h"
#include <logger.h>
#include <QMap>


class Connector
{
public:
    Connector()=default;
    ~Connector()=default;
    virtual bool openConnection() {return true;};
    virtual void closeConnection(){return;};
    virtual bool isConnectionOpened() const {return true;};
    virtual std::vector<User> execSelectUsers(std::string queryText)const
    {return std::vector<User>();};
    virtual std::vector<Track> execSelectTracks(std::string queryText)const
    {return std::vector<Track>();};
    virtual std::vector<Listening> execSelectListenings(std::string queryText)const
    {return std::vector<Listening>();};
    virtual int execCountQuery(std::string queryText) const {return 0;} ;
    virtual bool execNoReturnQuery(std::string queryText) const{return true;};
};

class QConnector : public Connector
{
private:
    QSqlDatabase db;

    QMap<int, QString> SubdDrivers = {
        {POSTGRES_SUBD, "QPSQL"},
        {SQLITE_SUBD, "QSQLITE"},
    };


public:
    QConnector(const ConnInfo &conf, int subd);
    ~QConnector();
    virtual bool openConnection() override;
    virtual void closeConnection()override;
    virtual bool isConnectionOpened() const override;
    virtual std::vector<User> execSelectUsers(std::string queryText)const override;
    virtual std::vector<Track> execSelectTracks(std::string queryText)const override;
    virtual std::vector<Listening> execSelectListenings(std::string queryText)const override;
    virtual int execCountQuery(std::string queryText) const override;
    virtual bool execNoReturnQuery(std::string queryText) const override;




};

#endif // CONNECTOR_H
