QT -= gui
QT += sql multimedia

CONFIG += c++11 console
CONFIG -= app_bundle
INCLUDEPATH += /home/julia/boost/

LIBS += "-L/home/julia/boost/stage/lib/" -lssl -lcrypto #-lssl -lcrypto libs for SHA256 in JWT generate algorytm
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
        ../BL/Config/serverconfig.cpp \
        ../BL/DTO/dtoconverter.cpp \
        ../BL/DTO/dtotrak.cpp \
        ../BL/DTO/dtotraklist.cpp \
        ../BL/DTO/dtouser.cpp \
        ../BL/Facades/httpfacade.cpp \
        ../BL/HTTPServices/authservice.cpp \
        ../BL/HTTPServices/favoriteservice.cpp \
        ../BL/HTTPServices/jwt_encrypt_alg.cpp \
        ../BL/HTTPServices/trakhttpservice.cpp \
        ../BL/HTTPServices/userhttpservice.cpp \
        ../BL/Resources/favoritesresource.cpp \
        ../BL/Resources/resconverter.cpp \
        ../BL/Resources/trakresource.cpp \
        ../BL/Resources/userresource.cpp \
        ../BL/Tools/tools.cpp \
        asyncserver.cpp \
        controller.cpp \
        main.cpp \
        mapper.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../BL/Config/serverconfig.h \
    ../BL/DTO/dtoconverter.h \
    ../BL/DTO/dtotrak.h \
    ../BL/DTO/dtotraklist.h \
    ../BL/DTO/dtouser.h \
    ../BL/Facades/httpfacade.h \
    ../BL/HTTPServices/authservice.h \
    ../BL/HTTPServices/favoriteservice.h \
    ../BL/HTTPServices/jwt_encrypt_alg.h \
    ../BL/HTTPServices/trakhttpservice.h \
    ../BL/HTTPServices/userhttpservice.h \
    ../BL/Resources/favoritesresource.h \
    ../BL/Resources/resconverter.h \
    ../BL/Resources/trakresource.h \
    ../BL/Resources/userresource.h \
    ../BL/Tools/tools.h \
    asyncserver.h \
    controller.h \
    ../BL/headers/constants.h \
    ../BL/headers/req_exceptions.h \
    mapper.h

unix:!macx: LIBS += -L$$PWD/../build-Logger-Desktop-Debug/ -lLogger

INCLUDEPATH += $$PWD/../Logger
DEPENDPATH += $$PWD/../Logger

unix:!macx: PRE_TARGETDEPS += $$PWD/../build-Logger-Desktop-Debug/libLogger.a



unix:!macx: LIBS += -L$$PWD/../build-DAL-Desktop-Debug/ -lDAL

INCLUDEPATH += $$PWD/../DAL/include
DEPENDPATH += $$PWD/../DAL/include
