#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>

class Subscribe
{
private:
    int id;
    QString name;
    int price;
    int max_time;
public:
    Subscribe();
    Subscribe(const QSqlRecord &rec);
};

#endif // SUBSCRIBE_H
