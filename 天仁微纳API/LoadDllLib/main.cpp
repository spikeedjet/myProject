#include <QCoreApplication>
#include "dlllib.h"
#include "tcpclient.h"
#include "communicationsprotocol.h"
#include "udpclient.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    //测试代码开始
    DllLib dLib;
    int result = dLib.test();
    qDebug() << "result:" <<result ;

    //测试TCP API
    TcpClient *tcp = new TcpClient();
    tcp->connectToServer("192.168.0.1",9959);

    //测试通信协议CommunicationsProtocol
    QByteArray data =  CommunicationsProtocol::instance()->handshake();
    qDebug() << data;

    //测试UDP
    qDebug() << UdpClient::getInstance1();

    /*
    程序输出：
        10:08:55: Starting D:\Code\MyProject\LoadDllLib\build\Qt_6_6_3_msvc2019_64-Debug\debug\LoadDllLib.exe...
        动态库里面函数的输出num： 10
        result: 10
        Attempting to connect to "192.168.0.1" : 9959
        Connection failed: "Socket operation timed out"
        "\x7F\xC0\x00\x01\x00\x05\x01\x00\x06"
        UdpClient(0x1670d084dc0)
    */

    return a.exec();
}
