QT -= gui
QT       += core gui network serialport testlib printsupport

TEMPLATE = lib
DEFINES += DLLLIB_LIBRARY

CONFIG += c++17 dll

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communicationsprotocol.cpp \
    dlllib.cpp \
    tcpclient.cpp \
    udpclient.cpp \
    utils.cpp

HEADERS += \
    communicationsprotocol.h \
    dllLib_global.h \
    dlllib.h \
    tcpclient.h \
    udpclient.h \
    utils.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
