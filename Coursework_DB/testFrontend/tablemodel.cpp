#include "tablemodel.h"


void TableModel::crearDataList()
{
    int i = 0;
    qDebug() << "очистка списка"  << trackList.size();
    while (!trackList.empty())
    {
        delete trackList.at(i);
        trackList.removeAt(i);
    }
    qDebug() << "очистка списка завершена"  << trackList.size();
}

TableModel::~TableModel()
{
    qDebug() << "TableModel destructor";
    this->crearDataList();
}

TableModel::TableModel(/*const QList<AbstractTableData *> &trackList_,*/
                                   QList<QString> headerList_, int n_btn):
    trackList(QList<AbstractTableData *>()),
    headerList(headerList_), n_columns(headerList_.size()+n_btn)
{

}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (section >= headerList.size())
            return QVariant();
        return headerList.at(section);
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return trackList.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return n_columns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() >= trackList.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QList<QVariant> varList = trackList.at(index.row())->getVarList();

        if (index.column() >=  varList.size())
            return QVariant();

        return varList.at(index.column());

    }
    return QVariant();
}

QVariant TableModel::getId(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() >= trackList.size()) return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QVariant id = trackList.at(index.row())->getId();
        return id;
    }

    return QVariant();
}

void TableModel::resetData(const QList<AbstractTableData *> trackList_)
{
    beginResetModel(); //beginResetModel и endResetModel() чтобы кол-во строк в таблице тоже поменялось. Методы QAbstractItemModel

    this->crearDataList();
    trackList = trackList_;
    endResetModel();

    qDebug() << trackList.size();
}



