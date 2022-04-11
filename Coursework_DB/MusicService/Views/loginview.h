#ifndef LOGINVIEW_H
#define LOGINVIEW_H
#include <QString>
#include <QWidget>
#include "abstractview.h"
namespace Ui {
class LoginView;
}

class LoginView : public AbstractView
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();
    virtual int getType() const override;

private slots:
    void on_btnAutorize_clicked();
    void on_btnReg_clicked();
signals:
    void try_login(QString login, QString password);
    void btn_register_clicked();


private:
    Ui::LoginView *ui;
    int type=LOGIN_V;
};

#endif // LOGINVIEW_H
