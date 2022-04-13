#ifndef TRACKVIEW_H
#define TRACKVIEW_H
#include "tablemodeldelegate.h"
#include <QWidget>
#include "tablemodel.h"
#include "abstractview.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
namespace Ui {
class TrackView;
}

class TrackView : public AbstractView
{
    Q_OBJECT

public:
    explicit TrackView(QWidget *parent, TableModelDelegate *artistDelegate_);
    ~TrackView();
    void setData(QList <AbstractTableData *> trackList);
    void setDelegate(TableModelDelegate *trackDelegate);
    virtual int getType() const override;
    AbstractView *getPrevView() const;
    void setPrevView(AbstractView *value);

private slots:
    void on_btnMenu_clicked();
    void on_btnMenu_2_clicked();

signals:
    void to_menu();
    void to_previous(AbstractView *prev);

private:
    Ui::TrackView *ui;
    TableModel *trackTable;
    int type=TRACK_V;
    AbstractView *prevView;

 //   QMediaPlayer        *m_player;          // Проигрыватель треков
  //  QMediaPlaylist      *m_playlist;
};

#endif // TRACKVIEW_H
