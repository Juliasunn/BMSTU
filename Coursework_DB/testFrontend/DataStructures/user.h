#ifndef USER_H
#define USER_H
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>

class User
{
private:
    int id;
    QString login;
    QString password;// TODO: убрать
    int id_subscr;
    QDate subscr_end;
    int minutes_listerned;
public:
    User();
    User(QSqlRecord user_record);
};

#endif // USER_H
