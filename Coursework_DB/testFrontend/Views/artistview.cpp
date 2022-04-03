#include "artistview.h"
#include "ui_artistview.h"

ArtistView::ArtistView(QWidget *parent, QTrackTableModel *artistTable_, TableModelDelegate *artistDelegate_) :
    QWidget(parent),
    ui(new Ui::ArtistView),
    artistTable(artistTable_)
{
    qDebug() << "ArtistView(QWidget *parent) constructor called";
    ui->setupUi(this);
    //методы с ui-> можно использовать только после ui->setupUi(this)
    ui->tableView->setModel(artistTable);
    ui->tableView->setItemDelegate(artistDelegate_);
}

ArtistView::~ArtistView()
{
    qDebug() << "ArtistView destructor called";
    delete ui;
}

void ArtistView::setData(QList<AbstractTableModel *> artistList)
{

    artistTable-> resetData(artistList);
    //TODO: сделать что то с освобождениеинамической памяти из под элементов листа!

}

void ArtistView::setDelegate(TableModelDelegate *artistDelegate)
{
    ui->tableView->setItemDelegate(artistDelegate);
}



void ArtistView::on_btnMenu_clicked()
{
    emit to_menu();
}
