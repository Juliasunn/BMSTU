#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qtracktablemodel.h"
#include <QAbstractItemModel>
#include <QListView>
#include <QTableView>
#include <QStringListModel>
#include <QApplication>
#include <QMainWindow>
#include "trackdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
