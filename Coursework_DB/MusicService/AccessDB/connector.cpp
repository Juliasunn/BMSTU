#include "connector.h"

Connector::Connector()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("music");
    db.setUserName("julia");
    db.setPassword("201228");
}

Connector::~Connector()
{
    db.close();
}

int Connector::open_connection()
{
    if (!db.open())
    {
        qDebug() << "Database connection failed!";
        return -1;
    }
    return 0;

}

bool Connector::exec_non_query(QString &query_text) const
{
    QSqlQuery query = QSqlQuery(db);
    return (query.exec(query_text));
}

bool Connector::exec_param_query(QString &query_text, QList<QVariant> &vals) const
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare(query_text);

    for (auto val : vals)
        query.addBindValue(val);
    return (query.exec());
}

QList<QSqlRecord> Connector::exec_select(QString &query_text) const
{
  //  qDebug() << "Connector::exec_select";
    QSqlQuery query = QSqlQuery(db);
    query.exec(query_text);
    QList<QSqlRecord> result;

    while (query.next())
           result.push_back(query.record());

    //qDebug() << "Connector::exec_select";
    return result;

}

