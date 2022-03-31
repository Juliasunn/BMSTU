#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H
#include <QItemDelegate>
#include <QPushButton>
#include "qtracktablemodel.h"
#define ARTIST_SIG 1
#define TRACK_SIG 2
#define PLAYLIST_SIG 3

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
};

#endif // TRACKDELEGATE_H
