#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H
#include "tablemodeldelegate.h"
#include "tablemodel.h"
#include <QWidget>
#include <QString>
#include "abstractview.h"
class GenreFlags
{
    bool pop_fl;
    bool rock_fl;
    bool classic_fl;
    bool indi_fl;
    bool lofi_fl;
    bool rep_fl;
public:
    GenreFlags(bool pop_fl_, bool rock_fl_, bool classic_fl_,
               bool indi_fl_, bool lofi_fl_, bool rep_fl_):
            pop_fl(pop_fl_), rock_fl(rock_fl_), classic_fl(classic_fl_),
            indi_fl(indi_fl_), lofi_fl(lofi_fl_), rep_fl(rep_fl_) {};
    bool getPop_fl() const;
    bool getRock_fl() const;
    bool getClassic_fl() const;
    bool getIndi_fl() const;
    bool getLofi_fl() const;
    bool getRep_fl() const;
};


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
