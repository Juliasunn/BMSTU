#include "conversions.h"
QString add_quotes(QString str)
{
    QString str_with_quotes = QString("'")+str+QString("'");
    return str_with_quotes;
}


QString to_string(int val)
{
    char buf[50];
    int len = sprintf(buf, "%d", val);
    QString res(buf);
    return res;
}


QString to_arg(int val)
{
    QString str_with_quotes = add_quotes(to_string(val));
    return str_with_quotes;
}

QString to_arg(QString qstr)
{
    QString str_with_quotes = add_quotes(qstr);
    return str_with_quotes;
}
