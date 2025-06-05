#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include "dllLib_global.h"
#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class DLLLIB_EXPORT UdpClient : public QObject
{
    Q_OBJECT

public:
    static UdpClient* getInstance1();  // 宏动下实例
    static UdpClient* getInstanceMT(); // 宏动上实例
    static UdpClient* getInstanceMicroMotion(); //没有用到的实例
    bool sendMessage(const QByteArray& message);
    ~UdpClient();

signals:
    void messageReceived(const QByteArray& data, const QHostAddress& sender, quint16 senderPort);

private:
    UdpClient(const QHostAddress& address, quint16 port);  // 私有构造函数
    void readPendingDatagrams();

    QUdpSocket* udpSocket;
    QHostAddress targetAddress;
    quint16 targetPort;

    static UdpClient* m_instance1;  // 宏动下实例
    static UdpClient* m_instanceMT;  // 宏动上实例
    static UdpClient* m_instanceMicroMotion; //没有用到的实例

};

#endif // UDPCLIENT_H
