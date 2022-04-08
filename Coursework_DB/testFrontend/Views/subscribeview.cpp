#include "subscribeview.h"
#include "ui_subscribeview.h"

SubscribeView::SubscribeView(QWidget *parent, TableModelDelegate *td) :
    AbstractView(parent),
    ui(new Ui::SubscribeView)
    //sTable(tm), sCur(ctm)
{
    sTable = new TableModel(QList<QString>({" название ", " руб/мес ", " минут/мес "}), 1);
    sCur = new TableModel(QList<QString>({" название ", " руб/мес ", " минут/мес "}), 0);

    ui->setupUi(this);
    ui->tableView->setModel(sTable);
    ui->curSubscrView->setModel(sCur);
    ui->tableView->setItemDelegate(td);
    this->hide();
}

SubscribeView::~SubscribeView()
{
    qDebug() << "SubscribeView destructor";
    delete ui;
    if (sTable)
    {
        delete sTable;
        sTable = NULL;
    }
    if (sCur)
    {
        delete sCur;
        sCur = NULL;
    }
}

int SubscribeView::getType() const
{
    return type;
}

void SubscribeView::setData(QList<AbstractTableData *> sList)
{
    sTable-> resetData(sList);

}

void SubscribeView::setCurData(AbstractTableData *curSubscr)
{
    sCur->resetData(QList<AbstractTableData *>({curSubscr}));
}

void SubscribeView::setDelegate(TableModelDelegate *sDelegate)
{
    ui->tableView->setItemDelegate(sDelegate);

}

void SubscribeView::on_btnMenu_clicked()
{
    emit to_menu();
}
