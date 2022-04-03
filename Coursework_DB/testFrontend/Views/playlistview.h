#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H
#include "tablemodeldelegate.h"
#include <QWidget>
#include "qtracktablemodel.h"

namespace Ui {
class PlaylistView;
}

class PlaylistView : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistView(QWidget *parent, QTrackTableModel *playlistTable_, TableModelDelegate *playlistDelegate_);
    ~PlaylistView();
    void setData(QList <AbstractTableModel *> playlistList);
    void setDelegate(TableModelDelegate *playlistDelegate);
private slots:
    void on_btnMenu_clicked();
signals:
    void to_menu();

private:
    Ui::PlaylistView *ui;
   QTrackTableModel *playlistTable;
};

#endif // PLAYLISTVIEW_H
