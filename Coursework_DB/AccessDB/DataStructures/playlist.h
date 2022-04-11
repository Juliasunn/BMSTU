#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "abstracttabledata.h"

class Playlist : public AbstractTableData
{
private:
    QVariant id;
    QVariant name;
    QVariant num_track;
    QVariant id_user;
public:
    Playlist();
    ~Playlist();

    Playlist(QVariant name_, QVariant num_track_) : name(name_),
        num_track(num_track_){};

    Playlist(const QSqlRecord &rec);
    virtual QList<QVariant> getVarList() const override;
    virtual QVariant getId() const override;
};

#endif // PLAYLIST_H
