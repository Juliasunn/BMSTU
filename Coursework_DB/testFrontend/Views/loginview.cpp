#include "loginview.h"
#include "ui_loginview.h"
#include <QString>

LoginView::LoginView(QWidget *parent) :
    AbstractView(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
    this->hide();
}

LoginView::~LoginView()
{
    delete ui;
}

int LoginView::getType() const
{
    return type;
}

void LoginView::on_btnAutorize_clicked()
{
    QString login = ui->loginEntry->text();
    QString password = ui->passwordEntry->text();
    emit try_login(login, password);
}

void LoginView::on_btnReg_clicked()
{
    emit btn_register_clicked();

}
