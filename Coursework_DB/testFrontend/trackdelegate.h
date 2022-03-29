#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H
#include <QItemDelegate>
#include <QPushButton>
#include "qtracktablemodel.h"
class TrackDelegate : public QItemDelegate
{
     Q_OBJECT
public:
    TrackDelegate(QObject *parent = 0);
    ~TrackDelegate();
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // TRACKDELEGATE_H
