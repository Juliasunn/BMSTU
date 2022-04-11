#include "searchview.h"
#include "ui_searchview.h"

SearchView::SearchView(QWidget *parent/*, TableModel *atm, TableModel *ttmTableModelDelegate *md*/) :
    AbstractView(parent),
    ui(new Ui::SearchView)
{
    artistTM = new TableModel(QList<QString>({" имя ", " всего треков ", " прослушиваний "}), 1);
    trackTM = new TableModel(QList<QString>({" название ", " жанр ", " релиз ", " исполнитель ", " прослушиваний "}), 2);
    ui->setupUi(this);
    this->hide();
}

SearchView::~SearchView()
{
    qDebug() << "SearchView destructor";
    delete ui;
    if (artistTM)
    {
        delete artistTM;
        artistTM = NULL;
    }
    if (trackTM)
    {
        delete trackTM;
        trackTM=NULL;
    }
}



void SearchView::on_btnArtist_clicked()
{
    QString name = ui->artistEntry->text();
    bool popular_fl = ui->artistPopular->isChecked();
    bool ntrack_fl = ui->numTrack->isChecked();
    emit find_artust(name, popular_fl, ntrack_fl);
}

void SearchView::on_btnTrack_clicked()
{
    QString name = ui->trackEntry->text();
    bool popular_fl = ui->trackPopular->isChecked();
    bool date_fl = ui->trackDate->isChecked();
    GenreFlags gf = GenreFlags(ui->pop->isChecked(), ui->rok->isChecked(),
             ui->classic->isChecked(), ui->indi->isChecked(), ui->lofi->isChecked(),
                               ui->rep->isChecked());
    emit find_track(name, popular_fl, date_fl, gf);
}

void SearchView::on_btnMenu_clicked()
{
    emit to_menu();
}

void SearchView::setData(QList<AbstractTableData *> dataList)
{
    curTM->resetData(dataList);

}

void SearchView::setDelegate(TableModelDelegate *dataDelegate)
{

    ui->tableView->setItemDelegate(dataDelegate);

}

void SearchView::setArtistModel()
{
    ui->tableView->setModel(artistTM);
    curTM=artistTM;
}

void SearchView::setTrackModel()
{
    ui->tableView->setModel(trackTM);
    curTM=trackTM;
}

int SearchView::getType() const
{
    return type;
}

