#include "menuview.h"
#include "ui_menuview.h"

MenuView::MenuView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuView)
{
    ui->setupUi(this);
}

MenuView::~MenuView()
{
    delete ui;
}

void MenuView::on_btnPlaylists_clicked()
{
    emit show_playlists_btn_pressed(QVariant(ALL));

}

void MenuView::on_btnTracks_clicked()
{

    emit show_tracks_btn_pressed(QVariant(ALL), ALL);
}

void MenuView::on_btnArtisis_clicked()
{
    emit show_artists_btn_pressed(QVariant(ALL));

}

void MenuView::on_pushButton_clicked()
{
    emit show_subscrs_btn_pressed();
}

void MenuView::on_btnArtisis_2_clicked()
{
    emit show_search_view();
}
