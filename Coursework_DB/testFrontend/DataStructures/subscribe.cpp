#include "subscribe.h"

Subscribe::Subscribe()
{

}

Subscribe::Subscribe(const QSqlRecord &rec)
{
    qDebug() << "Subscribe called";
    id = rec.value(0).toInt();
    name = rec.value(1).toString();
    price = rec.value(2).toInt();
    max_time = rec.value(3).toInt();
    qDebug() << id << name << price << max_time;
}
