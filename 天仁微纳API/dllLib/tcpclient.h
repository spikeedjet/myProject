#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include "dllLib_global.h"

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class DLLLIB_EXPORT TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();

    bool connectToServer(const QString &host, quint16 port);

    void sendMessage(const QString &message);
    void disconnectFromServer();
    QTcpSocket *tcpSocket;


private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
signals:
    void dataReceived(const QString &data);  // 新增信号：当接收到数据时发出

private:
    QHostAddress serverAddress;
    quint16 serverPort;
};

#endif // TCPCLIENT_H
