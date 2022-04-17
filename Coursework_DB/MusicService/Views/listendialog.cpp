#include "listendialog.h"
#include "ui_listendialog.h"

ListenDialog::ListenDialog(QMediaPlayer *m_player_,  QString track_name,
                           QWidget *parent) :
    QDialog(parent), m_player(m_player_),
    ui(new Ui::ListenDialog)
{
   // setWindowTitle(QString("Воспроизведение"));
    ui->setupUi(this);
    ui->trackName->setText(track_name);
    m_player->play();
    setWindowTitle(QString("Воспроизведение"));
}

ListenDialog::~ListenDialog()
{
    m_player->stop();
    delete ui;

}

void ListenDialog::on_pushButton_clicked()
{
    m_player->play();
   // emit play();
}

void ListenDialog::on_pushButton_2_clicked()
{
     m_player->pause();
   // emit pause();
}
