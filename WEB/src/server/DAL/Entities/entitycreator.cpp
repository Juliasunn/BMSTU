#include "include/entitycreator.h"

User QEntityCreator::createUser(const QSqlRecord &rec)
{
   // qDebug() << "User called";
    int id = rec.value(ns_user::id_pos).toInt();
    std::string login = rec.value(ns_user::login_pos).toString().toStdString();
    std::string password = rec.value(ns_user::password_pos).toString().toStdString();
    int priveledges_level = rec.value(ns_user::priveledges_level_pos).toInt();

    ns_user::init_struct s = {id, login, password, priveledges_level};
    User u(s);
    return u;
    // qDebug() << id << name << genre << release_date << artist << listenings << time << file_name;
}

Track QEntityCreator::createTrack(const QSqlRecord &rec)
{
    ns_track::init_struct s;
   // qDebug() << "Track called";
    s.id = rec.value(ns_track::id_pos).toInt();
    s.name = rec.value(ns_track::name_pos).toString().toStdString();
    s.genre = rec.value(ns_track::genre_pos).toString().toStdString();
    s.artist = rec.value(ns_track::artist_pos).toString().toStdString();
    s.file_name = rec.value(ns_track::fname_pos).toString().toStdString();
    s.uuid = rec.value(ns_track::uuid_pos).toString().toStdString();
    //qDebug() << s.id << s.name.c_str() << s.genre<<s.artist.c_str();
    Track t(s);
    return t;
}

Listening QEntityCreator::createListening(const QSqlRecord &rec)
{
    ns_listening::init_struct s;
   // qDebug() << "Listening called";
    s.id = rec.value(ns_listening::id_pos).toInt();
    s.id_user = rec.value(ns_listening::iduser_pos).toInt();
    s.id_track = rec.value(ns_listening::idtrack_pos).toInt();
    s.date = rec.value(ns_listening::date_pos).toDateTime().toSecsSinceEpoch();
  //  qDebug() << s.id << s.id_user << s.id_track<<s.date;
    Listening l(s);
    return l;
}
