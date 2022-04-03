#ifndef REGVIEW_H
#define REGVIEW_H
#include <QString>
#include <QWidget>

namespace Ui {
class RegView;
}

class RegView : public QWidget
{
    Q_OBJECT

public:
    explicit RegView(QWidget *parent = nullptr);
    ~RegView();

private slots:
    void on_btnReg_clicked();
    void on_btnLogin_clicked();
signals:
    void try_register(QString, QString);
    void btn_login_clicked();

private:
    Ui::RegView *ui;
};

#endif // REGVIEW_H
