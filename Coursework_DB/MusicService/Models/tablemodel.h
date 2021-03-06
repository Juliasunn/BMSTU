#ifndef QTRACKTABLEMODEL_H
#define QTRACKTABLEMODEL_H
#include <QAbstractTableModel>
#include <QVariant>
#include "DataStructures/track.h"
//#include "trackdelegate.h"

class TableModel : public QAbstractTableModel
{
private:
    QList<AbstractTableData *> trackList;
    QList<QString> headerList;
    int n_columns;

    void crearDataList();
public:
    TableModel()=default;
    ~TableModel();
    TableModel(/*const QList<AbstractTableData *> &trackList_,*/ QList<QString> headerList_, int n_btn);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;

    virtual QVariant getId(const QModelIndex &index, int role=Qt::DisplayRole) const; //for getting an id inside delegate
    virtual AbstractTableData *getById(QVariant id); //for listening tracks
    virtual void resetData(const QList<AbstractTableData *> trackList_);
};

#endif // QTRACKTABLEMODEL_H
