#ifndef LISTENING_H
#define LISTENING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>

namespace ns_listening
{
enum columnPos
    {id_pos,
     iduser_pos,
     idtrack_pos,
     date_pos
    };

struct init_struct
{
    int id;
    int id_user;
    int id_track;
    long long date;
};

};

class Listening
{
    int id;
    int id_user;
    int id_track;
    long long date;
public:
    Listening()=default;
    Listening(ns_listening::init_struct st): id(st.id), id_user(st.id_user),
        id_track(st.id_track),  date(st.date){};
    int getId() const;
    int getId_user() const;
    int getId_track() const;
    long long getDate() const;

    std::string out(){return std::to_string(id).append(" ").append(std::to_string(id_user)).append(" ")
                .append(std::to_string(id_track)).append(" ").append(std::to_string(date));};
};

#endif // LISTENING_H
