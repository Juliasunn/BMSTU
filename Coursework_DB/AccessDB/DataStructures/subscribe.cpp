#include "subscribe.h"

QVariant Subscribe::getId() const
{
    return id;
}

Subscribe::Subscribe()
{
    
}

Subscribe::~Subscribe()
{
    qDebug() << "Subscribe destructor";
}

Subscribe::Subscribe(const QSqlRecord &rec)
{
    qDebug() << "Subscribe called";
    id = rec.value(0);
    name = rec.value(1);
    price = rec.value(2);
    max_time = rec.value(3);
    qDebug() << id << name << price << max_time;
}

QList<QVariant> Subscribe::getVarList() const
{
    return QList<QVariant>({name, price, max_time});

}
