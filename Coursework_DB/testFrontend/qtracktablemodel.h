#ifndef QTRACKTABLEMODEL_H
#define QTRACKTABLEMODEL_H
#include <QAbstractTableModel>
#include <QVariant>
#include "DataStructures/track.h"
//#include "trackdelegate.h"

class QTrackTableModel : public QAbstractTableModel
{
private:
    QList<Track> trackList;

public:
    QTrackTableModel();
    QTrackTableModel(const QList<Track> &trackList);
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;
};

#endif // QTRACKTABLEMODEL_H
