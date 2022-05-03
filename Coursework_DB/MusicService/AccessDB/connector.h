#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord>
#include <vector>
#include <QSqlQuery>
#include <QList>
#include "conversions.h"
class Connector
{
private:
    QSqlDatabase db;
public:
    Connector();
    ~Connector();
    int open_connection();
    QList<QSqlRecord> exec_select(QString &query_text) const;
    bool exec_non_query(QString &query_text) const; //выпполняет инструкцию (добавление/удаление/обновление)
    bool exec_param_query(QString &query_text, QList<QVariant> &vals) const;
};

#endif // CONNECTOR_H
