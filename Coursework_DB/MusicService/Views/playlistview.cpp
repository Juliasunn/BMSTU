#include "playlistview.h"
#include "ui_playlistview.h"

PlaylistView::PlaylistView(QWidget *parent, TableModelDelegate *playlistDelegate_) :
    AbstractView(parent),
    ui(new Ui::PlaylistView)
   // playlistTable(playlistTable_)
{
  playlistTable = new TableModel( QList<QString>({" название ", " всего треков "}), 2);
  ui->setupUi(this);
  ui->tableView->setModel(playlistTable);
  ui->tableView->setItemDelegate(playlistDelegate_);
  this->hide();
}

PlaylistView::~PlaylistView()
{
    qDebug() << "PlaylistView destructor";
    delete ui;
    if (playlistTable)
    {
        delete playlistTable;
        playlistTable=NULL;
    }

}

void PlaylistView::setData(QList<AbstractTableData *> playlistList)
{
    playlistTable-> resetData(playlistList);
}

void PlaylistView::setDelegate(TableModelDelegate *playlistDelegate)
{
    ui->tableView->setItemDelegate(playlistDelegate);
}

int PlaylistView::getType() const
{
    return type;
}

void PlaylistView::on_btnMenu_clicked()
{
    emit to_menu();
}

void PlaylistView::on_btnMenu_2_clicked()
{
    emit to_previous(prevView);
}

AbstractView *PlaylistView::getPrevView() const
{
    return prevView;
}

void PlaylistView::setPrevView(AbstractView *value)
{
    prevView = value;
}
