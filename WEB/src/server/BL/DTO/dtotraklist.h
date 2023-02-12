#ifndef DTOTRAKLIST_H
#define DTOTRAKLIST_H
#include <string_view>
#include <string>
#include </home/julia/boost/boost/json.hpp>
#include "../Tools/tools.h"
#include "../headers/req_exceptions.h"
#include "dtotrak.h"

class DTOTrakList
{
    std::vector<DTOTrak> vec;
public:
    DTOTrakList()=default;
    boost::json::array getJson() const;
    std::vector<DTOTrak> getVec() const;
    void setVec(const std::vector<DTOTrak> &value);
};

#endif // DTOTRAKLIST_H
