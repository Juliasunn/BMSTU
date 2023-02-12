#ifndef QUERYPARAM_H
#define QUERYPARAM_H
#include <string>
#include <stdio.h>
#include <map>


enum Column
{U_ID, U_LOGIN, U_PASSWORD, U_LEVEL,
T_ID, T_NAME, T_DATE, T_GENRE, T_ARTIST, T_FILE, T_UUID,
L_ID, L_USER, L_TRACK,
UT_ID, UT_USER, UT_TRACK, EMPTY};

enum Table
{USER_T, TRACK_T, LISTEN_T, UT_T};


class QueryParam
{
    Column c;
    std::string sign;
    std::string value;
public:
    QueryParam(Column c_, std::string s, std::string v): c(c_), sign(s) {value="'"+v+"'";};
    QueryParam(Column c_, std::string v): c(c_), sign("="){value="'"+v+"'";};
    QueryParam(Column c_, int v): c(c_), sign("="), value(std::to_string(v)){};

    std::string getColName(std::map<int, std::string> DBCols) const;
   // std::string getSign() const;
    std::string getValue() const;
    std::string getCondition(std::map<int, std::string> DBCols) const;
};

#endif // QUERYPARAM_H
