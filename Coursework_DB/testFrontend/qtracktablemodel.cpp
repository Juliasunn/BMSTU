#include "qtracktablemodel.h"

QTrackTableModel::QTrackTableModel()
{

}

QTrackTableModel::QTrackTableModel(const QList<AbstractTableModel *> &trackList_,
                                   QList<QString> headerList_, int n_btn): trackList(trackList_),
    headerList(headerList_), n_columns(headerList_.size()+n_btn)
{

}

QVariant QTrackTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int QTrackTableModel::rowCount(const QModelIndex &parent) const
{
    return trackList.size();
}

int QTrackTableModel::columnCount(const QModelIndex &parent) const
{
    return n_columns;
}

QVariant QTrackTableModel::data(const QModelIndex &index, int role) const
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

QVariant QTrackTableModel::getId(const QModelIndex &index, int role) const
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

void QTrackTableModel::resetData(const QList<AbstractTableModel *> &trackList_)
{
    beginResetModel(); //beginResetModel и endResetModel() чтобы кол-во строк в таблице тоже поменялось. Методы QAbstractItemModel
    trackList = trackList_;
    endResetModel();

    qDebug() << trackList.size();
}



