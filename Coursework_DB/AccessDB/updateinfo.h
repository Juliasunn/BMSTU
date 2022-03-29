#ifndef UPDATEINFO_H
#define UPDATEINFO_H
#include "connector.h"

class UpdateInfo
{
public:
    UpdateInfo() = delete;
    static bool update_listern_time(Connector &conn, int id_user, int new_listern_time /*in minutes*/);
    static bool update_listern_time(Connector &conn, int id_user); //в ноль
    static bool update_subscribe(Connector &conn, int id_user, int new_subscr_id, int num_month /*на сколько мес подписка*/);
};

#endif // UPDATEINFO_H
