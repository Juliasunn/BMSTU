#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H
#include <QWidget>
#include <QObject>
#define LOGIN_V 1
#define REG_V 2
#define MENU_V 3

#define SUBSCR_V 4
#define PLAYLIST_V 5
#define SEARCH_V 6
#define TRACK_V 7
#include <QMessageBox>
class AbstractView : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractView(QWidget *parent = nullptr): QWidget(parent){};
     virtual int getType() const;
};

#endif // ABSTRACTVIEW_H
