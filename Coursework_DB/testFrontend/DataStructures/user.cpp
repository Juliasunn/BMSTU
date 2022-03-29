#include "user.h"

User::User()
{

}

User::User(QSqlRecord user_record)
{
    qDebug() << "User called";
    id = user_record.value(0).toInt();
    login = user_record.value(1).toString();
    password = user_record.value(2).toString();// TODO: убрать
    id_subscr = user_record.value(3).toInt();
    subscr_end = user_record.value(4).toDate();
    minutes_listerned = user_record.value(5).toInt();
    qDebug() << id << login << password << id_subscr << subscr_end << minutes_listerned;
}
