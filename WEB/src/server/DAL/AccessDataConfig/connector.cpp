#include "include/connector.h"
#include <QSqlError>
QConnector::QConnector(const ConnInfo &conf, int subd)
{
    //qDebug() << "QConnector constructor";
    switch (subd)
    {
    case(POSTGRES_SUBD):
        db = QSqlDatabase::addDatabase(SubdDrivers[POSTGRES_SUBD]);
        db.setUserName(conf.getNameUser().c_str());
        db.setPassword(conf.getPassword().c_str());
        break;
    case(SQLITE_SUBD):
        db = QSqlDatabase::addDatabase(SubdDrivers[SQLITE_SUBD]);
         break;
    default:
        Logger::ErrorMsg("no driver for such SUBD type: "+std::to_string(subd));
        throw confile_exception();

    }
    db.setDatabaseName(conf.getNameDB().c_str());

}

QConnector::~QConnector()
{
    db.close();
}

bool QConnector::openConnection()
{
    if (!db.open())
    {
        throw db_exception();
    }
    Logger::InfoMsg("DB connection opened");
    return true;
}

void QConnector::closeConnection()
{
    db.close();
    Logger::InfoMsg("DB connection closed");
}

bool QConnector::isConnectionOpened() const
{
    return db.isOpen();
}

std::vector<User> QConnector::execSelectUsers(std::string queryText) const
{
    if (!isConnectionOpened())
        throw db_not_open_exception();

    QSqlQuery query = QSqlQuery(db);
    if (!query.exec(queryText.c_str()))
        throw invalid_query_exception();
    std::vector<User> users;

     while (query.next())
           users.push_back(QEntityCreator::createUser(query.record()));
     return users;
}

std::vector<Track> QConnector::execSelectTracks(std::string queryText) const
{
    if (!isConnectionOpened())
        throw db_not_open_exception();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(queryText.c_str()))
        throw invalid_query_exception();

    std::vector<Track> tracks;

     while (query.next())
           tracks.push_back(QEntityCreator::createTrack(query.record()));
     return tracks;
}

std::vector<Listening> QConnector::execSelectListenings(std::string queryText) const
{
    if (!isConnectionOpened())
        throw db_not_open_exception();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(queryText.c_str()))
        throw invalid_query_exception();
    std::vector<Listening> l;

     while (query.next())
           l.push_back(QEntityCreator::createListening(query.record()));
     return l;
}

int QConnector::execCountQuery(std::string queryText) const
{
    if (!isConnectionOpened())
        throw db_not_open_exception();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(queryText.c_str()))
    {
        qDebug() << query.lastError().text();
        throw invalid_query_exception();
    }

    if (query.next())
    {
        return query.record().value(0).toInt();
    }
    return 0;
}

bool QConnector::execNoReturnQuery(std::string queryText) const
{
    if (!isConnectionOpened())
        throw db_not_open_exception();

    QSqlQuery query = QSqlQuery(db);

    if (!query.exec(queryText.c_str()))
        throw invalid_query_exception();
    return true;
}
