#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H
#include "Models/tablemodeldelegate.h"
#include <QWidget>
#include "Models/tablemodel.h"
#include "abstractview.h"
namespace Ui {
class PlaylistView;
}

class PlaylistView : public AbstractView
{
    Q_OBJECT

public:
    explicit PlaylistView(QWidget *parent, TableModelDelegate *playlistDelegate_);
    ~PlaylistView();
    void setData(QList <AbstractTableData *> playlistList);
    void setDelegate(TableModelDelegate *playlistDelegate);
    virtual int getType() const override;
    AbstractView *getPrevView() const;
    void setPrevView(AbstractView *value);

private slots:
    void on_btnMenu_clicked();
    void on_btnMenu_2_clicked();

    void on_btnMenu_3_clicked();

signals:
    void to_menu();
    void to_previous(AbstractView *prev);
    void addAlbum(QString name);

private:
    Ui::PlaylistView *ui;
   TableModel *playlistTable;
   int type=PLAYLIST_V;
   AbstractView *prevView;
};

#endif // PLAYLISTVIEW_H
