#include "regview.h"
#include "ui_regview.h"

RegView::RegView(QWidget *parent) :
    AbstractView(parent),
    ui(new Ui::RegView)
{
    ui->setupUi(this);
    this->hide();
}

RegView::~RegView()
{
    delete ui;
}

int RegView::getType() const
{
    return type;
}

void RegView::on_btnReg_clicked()
{
    QString login = ui->loginEntry->text();
    QString password = ui->passwordEntry->text();
    QString repPassword = ui->repPasswordEntry->text();
    if (login.length()<3)
        QMessageBox::warning(this, "Ошибка", "Логин должен содержать минимум 3 символа");
    else if (password.length()<4)
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать минимум 3 символа");

    else if (password == repPassword)
        emit try_register(login, password);
    else
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают");


}

void RegView::on_btnLogin_clicked()
{
    emit btn_login_clicked();

}
