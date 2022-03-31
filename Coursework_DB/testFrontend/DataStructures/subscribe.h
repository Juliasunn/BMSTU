#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H
#include "abstracttablemodel.h"

class Subscribe : public AbstractTableModel
{
private:
    QVariant id;
    QVariant name;
    QVariant price;
    QVariant max_time;
public:
    Subscribe();
    Subscribe(const QSqlRecord &rec);
    virtual QList<QVariant> getVarList() const override;
    virtual QVariant getId() const override;
};

#endif // SUBSCRIBE_H
