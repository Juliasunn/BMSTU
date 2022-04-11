#ifndef UPDATEINFO_H
#define UPDATEINFO_H
#include "connector.h"

class UpdateInfo
{
public:
    UpdateInfo() = delete;
    static bool update_listern_time(Connector &conn, int user_id, int track_id);
    //static bool update_listern_time(Connector &conn, int id_user); //в ноль
    static bool update_subscribe(Connector &conn, int id_user, int new_subscr_id=1, int num_month=1 /*на сколько мес подписка*/);
};

#endif // UPDATEINFO_H
