#ifndef REGVIEW_H
#define REGVIEW_H
#include <QString>
#include <QWidget>
#include "abstractview.h"
namespace Ui {
class RegView;
}

class RegView : public AbstractView
{
    Q_OBJECT

public:
    explicit RegView(QWidget *parent = nullptr);
    ~RegView();
    virtual int getType() const override;

private slots:
    void on_btnReg_clicked();
    void on_btnLogin_clicked();
signals:
    void try_register(QString, QString);
    void btn_login_clicked();

private:
    Ui::RegView *ui;
    int type=REG_V;
};

#endif // REGVIEW_H
