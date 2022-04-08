#ifndef SUBSCRIBEVIEW_H
#define SUBSCRIBEVIEW_H
#include "tablemodeldelegate.h"
#include <QWidget>
#include "tablemodel.h"
#include "abstractview.h"
namespace Ui {
class SubscribeView;
}

class SubscribeView : public AbstractView
{
    Q_OBJECT

public:
    explicit SubscribeView(QWidget *parent, TableModelDelegate *td);
    ~SubscribeView();
    virtual int getType() const override;
    void setCurData(AbstractTableData *curSubscr);
    void setData(QList <AbstractTableData *> sList);
    void setDelegate(TableModelDelegate *sDelegate);
private slots:
    void on_btnMenu_clicked();
signals:
    void to_menu();

private:
    Ui::SubscribeView *ui;
    TableModel *sTable, *sCur;
    int type=SUBSCR_V;
};

#endif // SUBSCRIBEVIEW_H
