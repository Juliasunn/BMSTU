#ifndef CHECKINFO_H
#define CHECKINFO_H
#include "connector.h"
class CheckInfo
{
public:
    CheckInfo() = delete;
    static bool is_user_exist(const Connector &conn, QString login, QString password);
    static bool is_subscribe_expiled(Connector &conn, int user_id);
    static bool is_login_taken(Connector &conn, QString &login);
    static bool is_song_in_album(Connector &conn, int album_id, int song_id);
    static bool check_time_limit(Connector &conn, int user_id, int track_id);

    static bool check_album_limit(Connector &conn, int user_id);
    static bool check_album_exists(Connector &conn, int user_id, QString album_name);
};

#endif // CHECKINFO_H
