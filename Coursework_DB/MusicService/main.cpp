#include "Views/mainwindow.h"
#include "AccessDB/connector.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connector con;
    con.open_connection();

    Repository repo(con);

    MainWindow w;
    Controller control(w.getWidget(), repo);
    w.show();
    return a.exec();
}
