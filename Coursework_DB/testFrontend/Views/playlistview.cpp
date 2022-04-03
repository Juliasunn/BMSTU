#include "playlistview.h"
#include "ui_playlistview.h"

PlaylistView::PlaylistView(QWidget *parent, QTrackTableModel *playlistTable_, TableModelDelegate *playlistDelegate_) :
    QWidget(parent),
    ui(new Ui::PlaylistView),
    playlistTable(playlistTable_)
{
  ui->setupUi(this);
  ui->tableView->setModel(playlistTable);
  ui->tableView->setItemDelegate(playlistDelegate_);
}

PlaylistView::~PlaylistView()
{
    delete ui;
}

void PlaylistView::setData(QList<AbstractTableModel *> playlistList)
{
    playlistTable-> resetData(playlistList);
}

void PlaylistView::setDelegate(TableModelDelegate *playlistDelegate)
{
    ui->tableView->setItemDelegate(playlistDelegate);
}

void PlaylistView::on_btnMenu_clicked()
{
    emit to_menu();
}
