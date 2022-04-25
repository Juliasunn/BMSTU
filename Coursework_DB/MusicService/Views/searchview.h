#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H
#include "Models/tablemodeldelegate.h"
#include "Models/tablemodel.h"
#include <QWidget>
#include <QString>
#include "abstractview.h"
#include "AccessDB/getinfo.h"

namespace Ui {
class SearchView;
}

class SearchView : public AbstractView
{
    Q_OBJECT

public:
    explicit SearchView(QWidget *parent);
    ~SearchView();

    void setData(QList <AbstractTableData *> dataList);
    void setDelegate(TableModelDelegate *dataDelegate);
    void setArtistModel();
    void setTrackModel();
    virtual int getType() const override;
    virtual AbstractTableData *getById(QVariant id); //for listening tracks

private slots:
    void on_btnArtist_clicked();
    void on_btnTrack_clicked();
    void on_btnMenu_clicked();

signals:
    void find_artust(QString name, bool popular_fl, bool ntrack_fl);
    void find_track(QString name, bool popular_fl, bool date_fl, GenreFlags);
    void to_menu();

private:
    Ui::SearchView *ui;
    TableModel *artistTM, *trackTM, *curTM=NULL;
    int type=SEARCH_V;
};

#endif // SEARCHVIEW_H
