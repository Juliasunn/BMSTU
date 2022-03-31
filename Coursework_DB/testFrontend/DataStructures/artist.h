#ifndef ARTIST_H
#define ARTIST_H
#include "abstracttablemodel.h"

class Artist : public AbstractTableModel
{
private:
    QVariant id;
    QVariant name;
    QVariant num_track;
    QVariant listenings;
public:
    Artist();

    Artist(QVariant name_, QVariant num_track_, QVariant listenings_, QVariant id_ = 0) : name(name_),
        num_track(num_track_), listenings(listenings_), id(id_){};

    Artist(QSqlRecord &artist_rec);
    virtual QList<QVariant> getVarList() const override;
    virtual QVariant getId() const override;
};

#endif // ARTIST_H
