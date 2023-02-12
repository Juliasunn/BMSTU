#ifndef TRACK_H
#define TRACK_H
#include <QString>
#include "DAL_global.h"

namespace ns_track
{
enum columnPos
    {id_pos,
     name_pos,
     genre_pos,
     artist_pos,
     fname_pos,
     uuid_pos
    };

struct init_struct
{
    int id;
    std::string name; //show
    std::string genre; //show
    std::string artist; //show
    std::string file_name;
    std::string uuid;
};

};

enum Genre {POP, REP, ROCK, INDI};

class DAL_EXPORT  Track
{
private:
    int id;
    std::string name; //show
    std::string genre; //show
   // QVariant release_date; //show
    std::string artist; //show
    std::string file_name;
    std::string uuid;
    int numListenings;
public:
    Track()=default;
    ~Track()=default;

    Track(ns_track::init_struct st) : name(st.name), genre(st.genre),
        artist(st.artist), file_name(st.file_name), id(st.id), uuid(st.uuid), numListenings(0){};
    int getId() const;
    std::string getName() const;
    std::string getArtist() const;
    //int getListenings() const;
    std::string getFile_name() const;

    std::string out(){return std::to_string(id).append(" ").append(name).append(" ")
                .append(genre).append(" ").append(artist).append(" ").
                append(file_name);};



    int getNumListenings() const;
    void setNumListenings(int value);
    std::string toString(){return name.append(" ")
                .append(genre).append(" ").append(artist).append(" ").
                append(file_name);};
    std::string getGenre() const;
    std::string getUuid() const;
    void setUuid(const std::string &value);
};

#endif // TRACK_H
