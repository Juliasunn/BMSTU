#include "listendialog.h"
#include "ui_listendialog.h"

ListenDialog::ListenDialog(QMediaPlayer *m_player_,
                           QWidget *parent) :
    QDialog(parent), m_player(m_player_),
    ui(new Ui::ListenDialog)
{
   // setWindowTitle(QString("Воспроизведение"));
    ui->setupUi(this);
   // ui->trackName->setText(track_name);
    m_player->play();
    setWindowTitle(QString("Воспроизведение"));
    this->connect(this, &QDialog::rejected, this, &ListenDialog::reject);
}

void ListenDialog::setText(QString track_name)
{
    ui->trackName->setText(track_name);
}

ListenDialog::~ListenDialog()
{
    m_player->stop();
    delete ui;

}

void ListenDialog::reject()
{
    m_player->stop();
    this->hide();
    qDebug() << "reject called";
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
