QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataStructures/artist.cpp \
    DataStructures/playlist.cpp \
    DataStructures/subscribe.cpp \
    DataStructures/track.cpp \
    DataStructures/user.cpp \
    Views/abstractview.cpp \
    Views/loginview.cpp \
    Views/mainwindow.cpp \
    Views/menuview.cpp \
    Views/playlistview.cpp \
    Views/regview.cpp \
    Views/searchview.cpp \
    Views/subscribeview.cpp \
    Views/trackview.cpp \
    controller.cpp \
    listmodel.cpp \
    main.cpp \
    repository.cpp \
    tablemodel.cpp \
    tablemodeldelegate.cpp \

HEADERS += \
    DataStructures/abstracttabledata.h \
    DataStructures/artist.h \
    DataStructures/playlist.h \
    DataStructures/subscribe.h \
    DataStructures/track.h \
    DataStructures/user.h \
    Views/abstractview.h \
    Views/loginview.h \
    Views/mainwindow.h \
    Views/menuview.h \
    Views/playlistview.h \
    Views/regview.h \
    Views/searchview.h \
    Views/subscribeview.h \
    Views/trackview.h \
    controller.h \
    listmodel.h \
    repository.h \
    tablemodel.h \
    tablemodeldelegate.h \

FORMS += \
    Views/loginview.ui \
    Views/mainwindow.ui \
    Views/menuview.ui \
    Views/playlistview.ui \
    Views/regview.ui \
    Views/searchview.ui \
    Views/subscribeview.ui \
    Views/trackview.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
