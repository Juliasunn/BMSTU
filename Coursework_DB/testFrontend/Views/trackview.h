#ifndef TRACKVIEW_H
#define TRACKVIEW_H
#include "tablemodeldelegate.h"
#include <QWidget>
#include "qtracktablemodel.h"

namespace Ui {
class TrackView;
}

class TrackView : public QWidget
{
    Q_OBJECT

public:
    explicit TrackView(QWidget *parent, QTrackTableModel *artistTable_, TableModelDelegate *artistDelegate_);
    ~TrackView();
    void setData(QList <AbstractTableModel *> trackList);
    void setDelegate(TableModelDelegate *trackDelegate);
private slots:
    void on_btnMenu_clicked();
signals:
    void to_menu();

private:
    Ui::TrackView *ui;
    QTrackTableModel *trackTable;
};

#endif // TRACKVIEW_H
