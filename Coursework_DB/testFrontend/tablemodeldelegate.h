#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H
#include <QItemDelegate>
#include <QPushButton>
#include "tablemodel.h"

#define ARTIST_TRACK_SIG 1//показать треки данного исполнителя

#define CHOOSE_SUBSCR_SIG 2//выбрать эту подписку

#define ADD_TO_PLAYLIST_SIG 3//добавить трек в плейлист
#define DEL_FROM_PLAYLIST_SIG 4//удалить трек из плейлиста
#define LISTERN_SIG 5//слушать трек

#define DEL_PLAYLIST_SIG 6 //удалить плейлист
#define PLAYLIST_TRACK_SIG 7  //перейти в плейлист
#define CHOOSE_PLAYLIST_SIG 8//выбрать плейлист для добавления


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
    void del_playlist(QVariant id);
    void choose_playlist(QVariant id);
};

#endif // TRACKDELEGATE_H
