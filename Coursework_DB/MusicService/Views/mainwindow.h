#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Models/tablemodel.h"
#include <QAbstractItemModel>
#include <QListView>
#include <QTableView>
#include <QStringListModel>
#include <QApplication>
#include <QMainWindow>
#include "Models/tablemodeldelegate.h"
#include "DataStructures/artist.h"
#include "DataStructures/playlist.h"
#include "abstractview.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget *getWidget();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
