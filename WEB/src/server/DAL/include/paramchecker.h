#ifndef PARAMCHECKER_H
#define PARAMCHECKER_H
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "exceptionsdb.h"
#include <QDebug>

class ParamChecker
{
private:
    std::vector<char> m_validSymbols;
public:
    bool checkParams(const std::vector<std::string> &params) {
        for (auto param : params) {
            if (!isValidParam(param)) {
                throw forbidden_symb_exception();
            }
        }
        qDebug() << "EVERYTHING OK!!!";
        return true;
    }

    bool isValidParam(const std::string &param){
        for (auto symb : param){
            if (std::find(m_validSymbols.begin(), m_validSymbols.end(), symb) == m_validSymbols.end() ){
                qDebug() << "INVALID SYM!"<<symb;
                return false;
            }
        }
        return true;
    }

    ParamChecker()=default;
    ParamChecker(const ParamChecker &val)=default;
    ParamChecker(std::vector<char> validSymbols):  m_validSymbols(validSymbols)
    {
        qDebug()<< "valid symb = "<<m_validSymbols;
    };
};

#endif // PARAMCHECKER_H
