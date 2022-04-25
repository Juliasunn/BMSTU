#ifndef MENUVIEW_H
#define MENUVIEW_H
#include <QVariant>
#include <QWidget>
#include "Models/listmodel.h"
#include "abstractview.h"
#include "DataStructures/abstracttabledata.h"
#define ALL 0

namespace Ui {
class MenuView;
}

class MenuView : public AbstractView
{
    Q_OBJECT

public:
    explicit MenuView(QWidget *parent = nullptr);
    ~MenuView();
    void setUserInfo(AbstractTableData *user);
    virtual int getType() const override;

private slots:
    void on_btnPlaylists_clicked();

    void on_pushButton_clicked();

    void on_btnArtisis_2_clicked();

signals:
    void show_artists_btn_pressed(QVariant id);
    void show_tracks_btn_pressed(QVariant id, int type);
    void show_playlists_btn_pressed(QVariant id);
    void show_subscrs_btn_pressed();
    void show_search_view();
private:
    Ui::MenuView *ui;
    int type=MENU_V;
    ListModel *userList;
};

#endif // MENUVIEW_H
