#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTrackTableModel *track_table = new QTrackTableModel();
   // QTableView *view = new QTableView();

    ui->tableView->setModel(track_table);

    TrackDelegate *tr_delegate = new TrackDelegate();
    ui->tableView->setItemDelegate(tr_delegate);
   // ui->tableView->setHorizontalScrollMode(Qt::ScrollBarAlwaysOff);
   // view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

