#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H
#include <QItemDelegate>
#include <QPushButton>
#include "qtracktablemodel.h"

#define ARTIST_TRACK_SIG 2
#define PLAYLIST_TRACK_SIG 3

#define ARTIST_SIG 1
#define PLAYLIST_SIG 4
#define CHOOSE_SUBSCR_SIG 5

#define ADD_TO_PLAYLIST_SIG 6
#define DEL_FROM_PLAYLIST_SIG 7
#define LISTERN_SIG 8

#define ARTIST_ID 1
#define PLAYLIST_ID 2

class TableModelDelegate : public QItemDelegate
{
     Q_OBJECT

private:
    QList<int> btn_pos;
    QList<QString> btn_names;
    QList<int> btn_sig;
    // TODO: QList<QDialog *> dg_windows;
public:
    TableModelDelegate(QObject *parent, QList<int> btn_pos, QList<QString> btn_names,
                       QList<int> btn_sig);
    ~TableModelDelegate();
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model,
                             const QStyleOptionViewItem &option, const QModelIndex &index) override;
signals:
    void show_artists_btn_pressed(QVariant id);
    void show_tracks_btn_pressed(QVariant id);
    void show_playlists_btn_pressed(QVariant id);
    void change_subscr(QVariant id);
    void play_track(QVariant id);
    void add_to_playlist(QVariant id);
    void del_from_playlist(QVariant id);
};

#endif // TRACKDELEGATE_H
