#include "mainwindow.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //QTrackTableModel *track_table = new QTrackTableModel();
    //QTableView *view = new QTableView();

   // view->setModel(track_table);
   // view->show();

    MainWindow w;
   w.show();
    return a.exec();
}
