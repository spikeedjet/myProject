#include "udpclient.h"
#include <QDebug>
#include <QNetworkDatagram>

// 初始化静态成员变量
UdpClient* UdpClient::m_instance1 = nullptr;
UdpClient* UdpClient::m_instanceMT = nullptr;
UdpClient* UdpClient::m_instanceMicroMotion = nullptr;

// 私有构造函数
UdpClient::UdpClient(const QHostAddress& address, quint16 port) : QObject(nullptr)
{
    udpSocket = new QUdpSocket(this);
    // 绑定到任意地址和端口（接收端）
    if (!udpSocket->bind()) {
        qDebug() << "UDP Socket bind failed:" << udpSocket->errorString();
    }

    // 连接信号和槽
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClient::readPendingDatagrams);

    // 设置目标地址和端口
    targetAddress = address;
    targetPort = port;
}

// 析构函数
UdpClient::~UdpClient()
{
    delete udpSocket;
}

// 获取第一个实例（目标地址1）
UdpClient* UdpClient::getInstance1()
{
    if (!m_instance1) {
        m_instance1 = new UdpClient(QHostAddress("192.168.0.7"), 5300);
    }
    return m_instance1;
}

// 获取第二个实例（目标地址2）
UdpClient* UdpClient::getInstanceMT()
{
    if (!m_instanceMT) {
        m_instanceMT = new UdpClient(QHostAddress("192.168.0.8"), 5300); // 不同的目标地址和端口
    }
    return m_instanceMT;
}

UdpClient* UdpClient::getInstanceMicroMotion()
{
    if (!m_instanceMicroMotion) {
        m_instanceMicroMotion = new UdpClient(QHostAddress("192.168.0.9"), 5300); // 不同的目标地址和端口
    }
    return m_instanceMicroMotion;
}

// 发送消息
bool UdpClient::sendMessage(const QByteArray& message)
{
    // qDebug() << "Send:" << message.toHex();
    if (!udpSocket || udpSocket->state() != QAbstractSocket::BoundState) {
        qDebug() << "UDP Socket not ready.";
        return false;
    }

    qint64 bytesWritten = udpSocket->writeDatagram(message, targetAddress, targetPort);
    if (bytesWritten == -1) {
        qDebug() << "Failed to send message:" << udpSocket->errorString();
        return false;
    }
    return true;
}

// 处理接收到的数据
void UdpClient::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        if (datagram.isValid()) {
            emit messageReceived(datagram.data(), datagram.senderAddress(), datagram.senderPort());
        }
    }
}
