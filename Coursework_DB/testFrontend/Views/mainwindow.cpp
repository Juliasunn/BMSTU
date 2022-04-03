#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   Controller *control = new Controller(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

