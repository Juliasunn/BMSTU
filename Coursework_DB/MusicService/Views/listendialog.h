#ifndef LISTENDIALOG_H
#define LISTENDIALOG_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class ListenDialog;
}

class ListenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListenDialog(QMediaPlayer *m_player, QWidget *parent = nullptr);
    ~ListenDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ListenDialog *ui;
    QMediaPlayer *m_player;
//signals:
 //   void play();
 //   void pause();
};

#endif // LISTENDIALOG_H
