#ifndef LOGINVIEW_H
#define LOGINVIEW_H
#include <QString>
#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:
    void on_btnAutorize_clicked();
    void on_btnReg_clicked();
signals:
    void try_login(QString login, QString password);
    void btn_register_clicked();

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
