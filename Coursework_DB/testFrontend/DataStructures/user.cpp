#include "user.h"

QVariant User::getId() const
{
    return id;
}

User::User()
{
    
}

User::User(QSqlRecord user_record)
{
    qDebug() << "User called";
    id = user_record.value(0);
    login = user_record.value(1);
    password = user_record.value(2);// TODO: убрать
    subscr = user_record.value(3);
    subscr_end = user_record.value(4);
    minutes_listerned = user_record.value(5);
    qDebug() << id << login << password << subscr << subscr_end << minutes_listerned;
}

QList<QVariant> User::getVarList() const
{
    return QList<QVariant>({id, login, subscr, subscr_end, minutes_listerned});
}
