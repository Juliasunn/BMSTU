#include "trackview.h"
#include "ui_trackview.h"

TrackView::TrackView(QWidget *parent, TableModelDelegate *trackDelegate_) :
    AbstractView(parent),
    ui(new Ui::TrackView)
   // trackTable(trackTable_)
{
    trackTable = new TableModel(QList<QString>({" название ", " жанр ", " релиз ", " исполнитель ", " прослушиваний "}), 2);
    ui->setupUi(this);
    ui->tableView->setModel(trackTable);
    ui->tableView->setItemDelegate(trackDelegate_);
    this->hide();
}

TrackView::~TrackView()
{
    qDebug() << "TrackView destructor";
    delete ui;
    qDebug() << "TrackView ui was deleted";
    if (trackTable)
    {
        qDebug() << "trackTable not null";
         delete trackTable;
        trackTable = NULL;
    }
   qDebug() << "TrackView was completely deleted";

}

void TrackView::setData(QList<AbstractTableData *> trackList)
{
    trackTable-> resetData(trackList);
}

void TrackView::setDelegate(TableModelDelegate *trackDelegate)
{
    ui->tableView->setItemDelegate(trackDelegate);

}

int TrackView::getType() const
{
    return type;

}

void TrackView::on_btnMenu_clicked()
{
    emit to_menu();
}

AbstractView *TrackView::getPrevView() const
{
    return prevView;
}

void TrackView::setPrevView(AbstractView *value)
{
    prevView = value;
}

void TrackView::on_btnMenu_2_clicked()
{
    emit to_previous(prevView);
}
