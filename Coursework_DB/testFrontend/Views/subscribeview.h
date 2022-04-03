#ifndef SUBSCRIBEVIEW_H
#define SUBSCRIBEVIEW_H
#include "tablemodeldelegate.h"
#include <QWidget>
#include "qtracktablemodel.h"

namespace Ui {
class SubscribeView;
}

class SubscribeView : public QWidget
{
    Q_OBJECT

public:
    explicit SubscribeView(QWidget *parent, QTrackTableModel *tm, TableModelDelegate *td);
    ~SubscribeView();

    void setData(QList <AbstractTableModel *> sList);
    void setDelegate(TableModelDelegate *sDelegate);
private slots:
    void on_btnMenu_clicked();
signals:
    void to_menu();

private:
    Ui::SubscribeView *ui;
    QTrackTableModel *sTable;
};

#endif // SUBSCRIBEVIEW_H
