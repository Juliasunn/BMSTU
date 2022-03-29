#include "trackdelegate.h"
#include <QtGui>
#include <QDialog>
#include <QApplication>
#include <QDebug>

TrackDelegate::TrackDelegate(QObject *parent) : QItemDelegate(parent)
{
    qDebug() << "TrackDelegate constructor";

}

TrackDelegate::~TrackDelegate()
{
    qDebug() << "TrackDelegate destructor";
}

void TrackDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QTrackTableModel *model = static_cast<const QTrackTableModel*>(index.model());

    qDebug() << model->data(index);
    painter->drawText(option.rect, model->data(index).toString());

    if (index.column() == 5 || index.column() == 6)
    {

        QStyleOptionButton button;
        QRect r = option.rect;//getting the rect of the cell

        button.rect = option.rect;

        if (index.column() == 5) button.text = "Play";
        else button.text = "Add";

        button.state = QStyle::State_Enabled;

        QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);
    }



}

bool TrackDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    qDebug() << index.column();
    QMouseEvent * e = (QMouseEvent *)event;
             int clickY = e->y();

    if (event->type() == QEvent::MouseButtonPress)
    {
        QRect r = option.rect;

        int y = r.top();//the Y coordinate
        int h = r.height();//button height
        if(index.column() == 5)
        {
            if( clickY > y && clickY < y + h )
            {
                qDebug() << clickY << y << y + h <<  index.row();
                QDialog * d = new QDialog();
                d->setGeometry(0,0,100,100);
                d->show();
            }
        }
    }

     return true;
}
