#ifndef USER_H
#define USER_H
#include "abstracttabledata.h"

class User : public AbstractTableData
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

    User(QVariant login_, QVariant subscr_, QVariant subscr_end_,
          QVariant minutes_listerned_, QVariant id_ = 0) : login(login_), subscr(subscr_),
        subscr_end(subscr_end_), minutes_listerned(minutes_listerned_), id(id_){};

    User(QSqlRecord user_record);
    virtual QList<QVariant> getVarList() const override;
    virtual QVariant getId() const override;
};

#endif // USER_H
