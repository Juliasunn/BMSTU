#ifndef LISTMODEL_H
#define LISTMODEL_H
#include <QAbstractListModel>
#include "DataStructures/abstracttabledata.h"
#include <QObject>

class ListModel : public QAbstractListModel
{
   // Q_OBJECT
public:
    ListModel(QList<QString> hl, QObject *parent= nullptr);
    virtual ~ListModel();
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual void resetData(AbstractTableData * modelData_);
private:
    AbstractTableData *modelData;
    QList<QString> headerList;

};

#endif // LISTMODEL_H
