#include "regview.h"
#include "ui_regview.h"

RegView::RegView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegView)
{
    ui->setupUi(this);
}

RegView::~RegView()
{
    delete ui;
}

void RegView::on_btnReg_clicked()
{
    QString login = ui->loginEntry->text();
    QString password = ui->passwordEntry->text();
    QString repPassword = ui->repPasswordEntry->text();

    if (password == repPassword)
        emit try_register(login, password);

}

void RegView::on_btnLogin_clicked()
{
    emit btn_login_clicked();

}
