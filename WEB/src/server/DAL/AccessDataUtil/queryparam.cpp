#include "include/queryparam.h"

std::string QueryParam::getColName(std::map<int, std::string> DBCols) const
{
    return DBCols[c];
}

std::string QueryParam::getValue() const
{
    return value;
}

std::string QueryParam::getCondition(std::map<int, std::string> DBCols) const
{
    std::string condition = DBCols[c] + sign + value;
    return condition;
}

