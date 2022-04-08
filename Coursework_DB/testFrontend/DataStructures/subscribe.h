#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H
#include "abstracttabledata.h"

class Subscribe : public AbstractTableData
{
private:
    QVariant id;
    QVariant name;
    QVariant price;
    QVariant max_time;
public:
    Subscribe();
    ~Subscribe();
    Subscribe(QVariant name_, QVariant price_, QVariant max_time_,
           QVariant id_ = 0) : name(name_), price(price_),
        max_time(max_time_), id(id_){};
    Subscribe(const QSqlRecord &rec);
    virtual QList<QVariant> getVarList() const override;
    virtual QVariant getId() const override;
};

#endif // SUBSCRIBE_H
