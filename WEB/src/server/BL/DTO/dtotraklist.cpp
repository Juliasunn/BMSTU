#include "dtotraklist.h"



std::vector<DTOTrak> DTOTrakList::getVec() const
{
    return vec;
}

void DTOTrakList::setVec(const std::vector<DTOTrak> &value)
{
    vec = value;
}

boost::json::array DTOTrakList::getJson() const
{
    boost::json::array vecJson;
    for (auto val : vec){
        vecJson.push_back(val.getJson());
    }
 //   qDebug()<< "ok2";
    return vecJson;
}
