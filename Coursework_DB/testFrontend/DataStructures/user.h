#ifndef USER_H
#define USER_H
#include "abstracttablemodel.h"

class User : public AbstractTableModel
{
private:
    QVariant id;
    QVariant login;
    QVariant password;// TODO: убрать
    QVariant subscr;
    QVariant subscr_end;
    QVariant minutes_listerned;
public:
    User();
    User(QSqlRecord user_record);
    virtual QList<QVariant> getVarList() const override;
    virtual QVariant getId() const override;
};

#endif // USER_H
