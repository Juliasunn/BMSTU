#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H
#include "tablemodeldelegate.h"
#include <QWidget>
#include "qtracktablemodel.h"

namespace Ui {
class ArtistView;
}

class ArtistView : public QWidget
{
    Q_OBJECT

public:
    explicit ArtistView(QWidget *parent, QTrackTableModel *artistTable_, TableModelDelegate *artistDelegate_);
    ~ArtistView();

    void setData(QList <AbstractTableModel *> artistList);
    void setDelegate(TableModelDelegate *artistDelegate);
private:    
    QTrackTableModel *artistTable ;
    Ui::ArtistView *ui;
};

#endif // ARTISTVIEW_H
