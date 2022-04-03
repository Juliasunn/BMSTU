#include "loginview.h"
#include "ui_loginview.h"
#include <QString>

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
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
