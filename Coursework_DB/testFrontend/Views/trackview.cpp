#include "trackview.h"
#include "ui_trackview.h"

TrackView::TrackView(QWidget *parent, QTrackTableModel *trackTable_, TableModelDelegate *trackDelegate_) :
    QWidget(parent),
    ui(new Ui::TrackView),
    trackTable(trackTable_)
{
    ui->setupUi(this);
    ui->tableView->setModel(trackTable);
    ui->tableView->setItemDelegate(trackDelegate_);
}

TrackView::~TrackView()
{
    delete ui;
}

void TrackView::setData(QList<AbstractTableModel *> trackList)
{
    trackTable-> resetData(trackList);
}

void TrackView::setDelegate(TableModelDelegate *trackDelegate)
{
    ui->tableView->setItemDelegate(trackDelegate);

}

void TrackView::on_btnMenu_clicked()
{
    emit to_menu();
}
