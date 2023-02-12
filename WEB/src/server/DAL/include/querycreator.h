#ifndef QUERYCREATOR_H
#define QUERYCREATOR_H
#include "queryparam.h"
#include <vector>
#include <stdio.h>
#include <map>
#include "track.h"


class QueryCreator
{
public:
    QueryCreator()=default;

    virtual std::string createSelectQuery(Table tableName,
           std::vector<Column> columns=std::vector<Column>(),
                          std::vector<QueryParam> params=std::vector<QueryParam>(),
                           Column sort_raw=EMPTY) {return "";};

    virtual std::string createUpdateQuery(Table tableName,
          std::vector<QueryParam> conds, std::vector<QueryParam> vals) {return "";};
    virtual std::string createInsertQuery(Table tableName,
                                         std::vector<QueryParam> params) {return "";};
    virtual std::string createCountQuery(Table tableName,
                                         std::vector<QueryParam> params) {return "";};
    virtual std::string createDeleteQuery(Table tableName,
                                         std::vector<QueryParam> params) {return "";};
    virtual std::string createJoinQuery(std::vector<Table> tableName,
                                        std::vector<Column> join_columns,
                                        std::vector<Column> columns=std::vector<Column>(),
                                         std::vector<QueryParam> params=std::vector<QueryParam>())
                                        {return "";};
public:
    virtual std::string getName(Genre g) const;

    const std::map<int, std::string> GenreNames = {
        {POP, "pop"},
        {REP, "rep"},
        {ROCK, "rock"},
        {INDI, "indi"},

    };

};



class PostgreQueryCreator : public QueryCreator
{
public:
    PostgreQueryCreator()=default;

    virtual std::string createSelectQuery(Table tableName,
           std::vector<Column> columns=std::vector<Column>(),
                          std::vector<QueryParam> params=std::vector<QueryParam>(),
                           Column sort_raw=EMPTY) override;

    virtual std::string createCountQuery(Table tableName,
                                         std::vector<QueryParam> params)  override;
    virtual std::string createUpdateQuery(Table tableName,
            std::vector<QueryParam> conds, std::vector<QueryParam> vals)  override;
    virtual std::string createInsertQuery(Table tableName,
                                         std::vector<QueryParam> params)  override;
    virtual std::string createDeleteQuery(Table tableName,
                                         std::vector<QueryParam> params) override;


    virtual std::string createJoinQuery(std::vector<Table> tableName,
                                        std::vector<Column> join_columns,
                                        std::vector<Column> columns=std::vector<Column>(),
                                         std::vector<QueryParam> params=std::vector<QueryParam>()) override;



    std::map<int, std::string> DBCols = {
        {U_ID, "MUser.id"},
        {U_LOGIN, "login"},
        {U_PASSWORD, "password"},
        {U_LEVEL, "priveledges_level"},

        {T_ID, "Track.id"},
        {T_NAME, "name"},
        {T_DATE, "release_date"},
        {T_GENRE, "genre"},
        {T_ARTIST, "artist"},
        {T_FILE, "file_name"},
        {T_UUID, "uuid"},

        {L_ID, "Listening.id"},
        {L_USER, "id_user"},
        {L_TRACK, "id_track"},

        {UT_ID, "UT.id"},
        {UT_USER, "id_user"},
        {UT_TRACK, "id_track"},
    };
    std::map<int, std::string> DBTables = {
        {USER_T, "MUser"},
        {TRACK_T, "Track"},
        {LISTEN_T, "Listening"},
        {UT_T, "UT"}

    };


private:
  //  std::string generate_id(Table);
    std::string createJoin(std::vector<Table> tableName,
                           std::vector<Column> join_columns);

    void convert(std::string &query_text, std::string sep, std::vector<QueryParam> params) const;

};


class SQLiteQueryCreator : public QueryCreator
{
public:
    SQLiteQueryCreator()=default;

    virtual std::string createSelectQuery(Table tableName,
           std::vector<Column> columns=std::vector<Column>(),
                          std::vector<QueryParam> params=std::vector<QueryParam>(),
                           Column sort_raw=EMPTY) override;

    virtual std::string createCountQuery(Table tableName,
                                         std::vector<QueryParam> params)  override;
    virtual std::string createUpdateQuery(Table tableName,
            std::vector<QueryParam> conds, std::vector<QueryParam> vals)  override;
    virtual std::string createInsertQuery(Table tableName,
                                         std::vector<QueryParam> params)  override;
    virtual std::string createDeleteQuery(Table tableName,
                                         std::vector<QueryParam> params) override;


    virtual std::string createJoinQuery(std::vector<Table> tableName,
                                        std::vector<Column> join_columns,
                                        std::vector<Column> columns=std::vector<Column>(),
                                         std::vector<QueryParam> params=std::vector<QueryParam>()) override;



    std::map<int, std::string> DBCols = {
        {U_ID, "MUser.id"},
        {U_LOGIN, "login"},
        {U_PASSWORD, "password"},

        {T_ID, "Track.id"},
        {T_NAME, "name"},

        {T_DATE, "release_date"},
        {T_GENRE, "genre"},

        {T_ARTIST, "artist"},
        {T_FILE, "file_name"},

        {L_ID, "Listening.id"},
        {L_USER, "id_user"},
        {L_TRACK, "id_track"},

        {UT_ID, "UT.id"},
        {UT_USER, "id_user"},
        {UT_TRACK, "id_track"},
    };
    std::map<int, std::string> DBTables = {
        {USER_T, "MUser"},
        {TRACK_T, "Track"},
        {LISTEN_T, "Listening"},
        {UT_T, "UT"}

    };


private:
    std::string createJoin(std::vector<Table> tableName,
                           std::vector<Column> join_columns);

    void convert(std::string &query_text, std::string sep, std::vector<QueryParam> params) const;

};


#endif // QUERYCREATOR_H
