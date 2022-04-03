#include "tablemodeldelegate.h"
#include <QtGui>
#include <QDialog>
#include <QApplication>
#include <QDebug>


TableModelDelegate::TableModelDelegate(QObject *parent, QList<int> btn_pos_, QList<QString> btn_names_,
                                       QList<int> btn_sig_) : QItemDelegate(parent),
    btn_pos(btn_pos_), btn_names(btn_names_), btn_sig(btn_sig_)
{
    qDebug() << "TrackDelegate constructor";
}

TableModelDelegate::~TableModelDelegate()
{
    qDebug() << "TrackDelegate destructor";
}

void TableModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QTrackTableModel *model = static_cast<const QTrackTableModel*>(index.model());

  //  qDebug() << model->data(index);
    painter->drawText(option.rect, model->data(index).toString());

    for (int i = 0; i<btn_pos.size(); i++)
    {
        if (index.column() == btn_pos.at(i))
        {
            QStyleOptionButton button;
            button.rect = option.rect;
            button.text = btn_names.at(i);
            button.state = QStyle::State_Enabled;

            QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);
        }
    }
}

bool TableModelDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                     const QStyleOptionViewItem &option, const QModelIndex &index)
{
   // qDebug() << index.column();
    QMouseEvent * e = (QMouseEvent *)event;
             int clickY = e->y();

    if (event->type() == QEvent::MouseButtonPress)
    {
        QRect r = option.rect;
        if( clickY > r.top() && clickY < r.top() + r.height() )
        {
            for (int i = 0; i<btn_pos.size(); i++)
            {
                if (index.column() == btn_pos.at(i))
                {
                    qDebug() << "PRESSED";

                    const QTrackTableModel *model = static_cast<const QTrackTableModel*>(index.model());
                    QVariant id = model->getId(index);
                    qDebug() << "id = " << id;
                    switch(btn_sig.at(i))
                    {
                    case ARTIST_SIG:
                        emit show_artists_btn_pressed(id);
                        break;
                    case ARTIST_TRACK_SIG:
                        emit show_tracks_btn_pressed(id);
                        break;
                    case PLAYLIST_TRACK_SIG:
                        emit show_tracks_btn_pressed(id);
                        break;
                    case PLAYLIST_SIG:
                        emit show_playlists_btn_pressed(id);
                        break;
                    case CHOOSE_SUBSCR_SIG:
                        emit change_subscr(id);
                        break;
                    case LISTERN_SIG:
                        emit play_track(id);
                        break;
                    case ADD_TO_PLAYLIST_SIG:
                        emit add_to_playlist(id);
                        break;
                    case DEL_FROM_PLAYLIST_SIG:
                        emit del_from_playlist(id);
                        break;
                    }

                }
            }
        }
    }
     return true;
}
