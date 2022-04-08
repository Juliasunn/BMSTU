#ifndef TRACK_H
#define TRACK_H
#include "abstracttabledata.h"

class Track : public AbstractTableData
{
private:
    QVariant id;
    QVariant name;
    QVariant id_genre;
    QVariant release_date;
    QVariant id_artist;
    QVariant listenings;
public:
    Track();
    ~Track();

    Track(QVariant name_, QVariant id_genre_, QVariant release_date_,
          QVariant id_artist_, QVariant listenings_, QVariant id_ = 0) : name(name_), id_genre(id_genre_),
        release_date(release_date_), id_artist(id_artist_), listenings(listenings_), id(id_){};

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
