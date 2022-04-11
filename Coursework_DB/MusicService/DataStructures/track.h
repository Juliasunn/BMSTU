#ifndef TRACK_H
#define TRACK_H
#include "abstracttabledata.h"

class Track : public AbstractTableData
{
private:
    QVariant id;
    QVariant name; //show
    QVariant genre; //show
    QVariant release_date; //show
    QVariant artist; //show
    QVariant listenings; //show
    QVariant time; //show
    QVariant file_name;
public:
    Track();
    ~Track();

    Track(QVariant name_, QVariant id_genre_, QVariant release_date_,
          QVariant id_artist_, QVariant listenings_, QVariant id_ = 0) : name(name_), genre(id_genre_),
        release_date(release_date_), artist(id_artist_), listenings(listenings_), id(id_){};

    Track(QSqlRecord &track_rec);

    virtual QVariant getId() const override;
    QVariant getName() const;
    QVariant getId_genre() const;
    QVariant getRelease_date() const;
    QVariant getId_artist() const;
    QVariant getListenings() const;

    virtual QList<QVariant> getVarList() const override;
};

#endif // TRACK_H
