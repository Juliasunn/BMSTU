#include "subscribeview.h"
#include "ui_subscribeview.h"

SubscribeView::SubscribeView(QWidget *parent, QTrackTableModel *tm, TableModelDelegate *td) :
    QWidget(parent),
    ui(new Ui::SubscribeView),
    sTable(tm)
{
    ui->setupUi(this);
    ui->tableView->setModel(sTable);
    ui->tableView->setItemDelegate(td);
}

SubscribeView::~SubscribeView()
{
    delete ui;
}

void SubscribeView::setData(QList<AbstractTableModel *> sList)
{
    sTable-> resetData(sList);

}

void SubscribeView::setDelegate(TableModelDelegate *sDelegate)
{
    ui->tableView->setItemDelegate(sDelegate);

}

void SubscribeView::on_btnMenu_clicked()
{
    emit to_menu();
}
