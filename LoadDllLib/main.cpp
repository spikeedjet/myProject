#include <QCoreApplication>
#include "dlllib.h"
#include "tcpclient.h"
#include "communicationsprotocol.h"
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

    TcpClient *tcp = new TcpClient();
    tcp->connectToServer("192.168.0.1",9959);

    // CommunicationsProtocol::instance()->findZeroing();
    // CommunicationsProtocol::Command::HANDSHAKE;

    QByteArray data =  CommunicationsProtocol::instance()->handshake();
    qDebug()<<data;

    return a.exec();
}
