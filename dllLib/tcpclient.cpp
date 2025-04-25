// #include "tcpclient.h"

// TcpClient::TcpClient(QObject *parent)
//     : QObject{parent}
// {}

#include "tcpclient.h"
#include <QNetworkProxy>
#include <QDebug>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);

    // 连接信号槽
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
}

TcpClient::~TcpClient()
{
    disconnectFromServer();
    delete tcpSocket;
}
bool TcpClient::connectToServer(const QString &host, quint16 port)
{
    serverAddress = QHostAddress(host);
    serverPort = port;

    qDebug() << "Attempting to connect to" << host << ":" << port;

    // 禁用代理
    tcpSocket->setProxy(QNetworkProxy::NoProxy);

    // 尝试连接
    tcpSocket->connectToHost(serverAddress, serverPort);

    // 等待连接结果，最多等待 3 秒
    if (tcpSocket->waitForConnected(3000)) {
        qDebug() << "Connection successful";
        return true;
    } else {
        qDebug() << "Connection failed:" << tcpSocket->errorString();

        return false;
    }
}

void TcpClient::sendMessage(const QString &message)
{
    if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Not connected to server!";
        return;
    }

    QByteArray data = message.toUtf8();
    qint64 bytesWritten = tcpSocket->write(data);

    if (bytesWritten == -1) {
        qDebug() << "Error sending message:" << tcpSocket->errorString();
    } else {
        // qDebug() << "Sent message:" << message;
    }
}

void TcpClient::disconnectFromServer()
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->disconnectFromHost();
    }
}

void TcpClient::onConnected()
{
    qDebug() << "Connected to server:" << serverAddress.toString() << ":" << serverPort;
}

void TcpClient::onDisconnected()
{
    qDebug() << "Disconnected from server";
}

void TcpClient::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QString receivedMessage = QString::fromUtf8(data);
    // qDebug() << "Received message:" << receivedMessage;

    // 发出信号，将接收到的数据发送出去
    emit dataReceived(receivedMessage);
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << tcpSocket->errorString();
}
