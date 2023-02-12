#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H
#include "user.h"
#include "track.h"
#include "listening.h"
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>


class EntityCreator
{
public:
    EntityCreator()=default;
};

class QEntityCreator
{
public:
    QEntityCreator()=delete;
    static Listening createListening(const QSqlRecord &rec);
    static User createUser(const QSqlRecord &rec);
    static Track createTrack(const QSqlRecord &rec);
};

#endif // ENTITYCREATOR_H
