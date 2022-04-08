#include "listmodel.h"

ListModel::ListModel(QList<QString> hl, QObject *parent) :// QAbstractListModel(parent),
    headerList(hl)
{
    qDebug() << "ListModel constructor";
    modelData = NULL;
}

ListModel::~ListModel()
{
    if (modelData)
    {
        delete modelData;
        modelData = NULL;
    }
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (!index.isValid() || !modelData)
        return QVariant();

    QList<QVariant> values = modelData->getVarList();
    if (index.row()+1 >= values.size())
        return QVariant();
    qDebug() << "ListModel data called" << values.at(index.row());
    return values.at(index.row()+1);
}

int ListModel::rowCount(const QModelIndex &parent) const
{
   // return 5;
    if (!modelData)
        return 0;
    qDebug() << "ListModel rowCount called" << modelData->getVarList().size();
    return headerList.size();

}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  //  return QVariant("123");
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
    {
        if (section >= headerList.size())
            return QVariant();
        return headerList.at(section);
    }
    return QVariant();
}

void ListModel::resetData(AbstractTableData * modelData_)
{
    qDebug() << "ListModel resetData called" << modelData_->getVarList().size();
    beginResetModel(); //beginResetModel и endResetModel() чтобы кол-во строк в таблице тоже поменялось. Методы QAbstractItemModel

   // delete modelData;
    modelData = modelData_;
    endResetModel();

}
