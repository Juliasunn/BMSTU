#include "qtracktablemodel.h"

QTrackTableModel::QTrackTableModel()
{

}

QTrackTableModel::QTrackTableModel(const QList<Track> &trackList_): trackList(trackList_)
{

}



QVariant QTrackTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("id");
        case 1:
            return QString("название");
        case 2:
            return QString("жанр");
        case 3:
            return QString("релиз");
        case 4:
            return QString("исполнитель");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

int QTrackTableModel::rowCount(const QModelIndex &parent) const
{
    return 6;
    //return trackList.size();
}

int QTrackTableModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}

QVariant QTrackTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
   // if (index.row() >= trackList.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
       // Track tr = trackList.at(index.row());
        switch (index.column())
        {
     //   case 0:
       //     return tr.getId();
      //  case 1:
       //     return tr.getName();
       // case 2:
        //    return tr.getId_genre();
       // case 3:
        //    return tr.getRelease_date();
       // case 4:
         //   return tr.getId_artist();
        default:
            return QVariant("(?)");
        }
    }
    else return QVariant();
}

//QTableWidgetItem * QTableModel::item 	( 	const QModelIndex &  	index	) 	const
//{
//if (!isValid(index))
 //        return 0;
  //   return tableItems.at(tableIndex(index.row(), index.column()));
//}
