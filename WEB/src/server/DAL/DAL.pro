QT -= gui
QT += sql multimedia

TEMPLATE = lib
DEFINES += DAL_LIBRARY

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
    #../Logger/logger.cpp \
    AccessDataConfig/connector.cpp \
    AccessDataConfig/conninfo.cpp \
    AccessDataUtil/accessordb.cpp \
    AccessDataUtil/paramchecker.cpp \
    AccessDataUtil/querycreator.cpp \
    AccessDataUtil/queryparam.cpp \
    AccessDataUtil/sqlitequerycreator.cpp \
    Config/dalconfig.cpp \
    Entities/entitycreator.cpp \
    Entities/listening.cpp \
    Entities/track.cpp \
    Entities/user.cpp \
    Repositories/listenrepo.cpp \
    Repositories/repocreator.cpp \
    Repositories/trackrepo.cpp \
    Repositories/userrepo.cpp \
    Repositories/usertrackrepo.cpp

HEADERS += \
    #../Logger/logger.h \
    include/paramchecker.h \
    Config/dalconfig.h \
    include/DAL_global.h \
    include/accessordb.h \
    include/connector.h \
    include/conninfo.h \
    include/dalconfig.h \
    include/entitycreator.h \
    include/exceptionsdb.h \
    include/listening.h \
    include/listenrepo.h \
    include/querycreator.h \
    include/queryparam.h \
    include/repocreator.h \
    include/track.h \
    include/trackrepo.h \
    include/user.h \
    include/userrepo.h \
    include/usertrackrepo.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../build-Logger-Desktop-Debug/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

unix:!macx: PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop-Debug/libLogger.a
