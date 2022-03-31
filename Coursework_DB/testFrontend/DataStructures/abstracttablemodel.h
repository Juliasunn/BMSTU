#ifndef ABSTRACTTABLEMODEL_H
#define ABSTRACTTABLEMODEL_H
#include <QList>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QString>
#include <QDebug>

class AbstractTableModel
{
public:
    AbstractTableModel();
    virtual QVariant getId() const = 0;//for getting the id in the controller
    virtual QList<QVariant> getVarList() const = 0; //for showing data in delegate
};

#endif // ABSTRACTTABLEMODEL_H
