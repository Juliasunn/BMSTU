#include "menuview.h"
#include "ui_menuview.h"

MenuView::MenuView(QWidget *parent) :
    AbstractView(parent),
    ui(new Ui::MenuView)
{
    ui->setupUi(this);
    userList = new ListModel( QList<QString>({"логин", "подписка", "до", "прослушано\n(мин)"}));
    ui->listView->setModel(userList);
    this->hide();
}

MenuView::~MenuView()
{
    delete ui;
}

void MenuView::setUserInfo(AbstractTableData *user)
{
    qDebug() << "setUserInfo called";
   // QList<QVariant> userInfo = user->getVarList();
    userList->resetData(user);
    //ui->uName->setText(userInfo[1].toString());
}

int MenuView::getType() const
{
    return type;
}

void MenuView::on_btnPlaylists_clicked()
{
    emit show_playlists_btn_pressed(QVariant(ALL));

}


void MenuView::on_pushButton_clicked()
{
    emit show_subscrs_btn_pressed();
}

void MenuView::on_btnArtisis_2_clicked()
{
    emit show_search_view();
}
