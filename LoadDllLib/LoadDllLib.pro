QT = core gui network serialport testlib printsupport

CONFIG += c++17 cmdline
CONFIG -= dll          # 确保客户端不定义动态库的导出宏

#完美解决：Debug\debug\moc_tcpclient.cpp:130: error: C2491: “TcpClient::staticMetaObject”: 不允许 dllimport 静态数据成员 的定义
DEFINES += DLLLIB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    communicationsprotocol.h \
    dllLib_global.h \
    dlllib.h \
    tcpclient.h



# 添加 DLL 库的链接
LIBS += -L$$PWD/ -ldllLib
