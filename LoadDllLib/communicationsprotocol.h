#ifndef COMMUNICATIONSPROTOCOL_H
#define COMMUNICATIONSPROTOCOL_H
#include "dllLib_global.h"

#include <QByteArray>
#include <QObject>

class DLLLIB_EXPORT CommunicationsProtocol: public QObject
{
    Q_OBJECT
public:

    // 获取单例实例的静态方法
    static CommunicationsProtocol* instance()
    {
        if (!m_instance) {
            m_instance = new CommunicationsProtocol();
        }
        return m_instance;
    }

    enum class Command : quint8 {
        HANDSHAKE = 0x01,
        REQUEST_DATA = 0x02,
        SET_STREAMING_MODE = 0x03,
        SET_SPEED = 0x19,
        STOP_MOTION = 0x20,
        ZERO_POSITION = 0x24,
        SINGLE_AXIS_MOTION = 0x25,
        MULTI_AXIS_MOTION = 0x26,
        JIENSHI_CLOSE_LOOP = 0x12
    };

    // 静态成员变量，保存唯一实例


    static inline CommunicationsProtocol* m_instance = nullptr;




    QByteArray handshake();
    QByteArray requestData();

    QByteArray setStreamingMode(bool enable);
    QByteArray stopMotion(quint8 stopType);
    QByteArray findZeroing();
    QByteArray singleAxisMotionWithInt(quint8 dataTypeAxis, qint32 position);
    QByteArray singleAxisMotionWithFloat(quint8 dataTypeAxis, float position);
    QByteArray multiAxisMotion(quint8 axisNumber, qint32 axis1Position, qint32 axis2Position,
                               qint32 axis3Position, qint32 axis4Position, qint32 axis5Position,
                               qint32 axis6Position);

    QByteArray sendInterferometerAxisData(qint32 axis1,qint32 axis2, qint32 axis3);

    QByteArray jienshiCloseLoop(qint8 mode, qint8 speedFlag, qint32 speedValue, qint8 noUseByte);

private:
    QByteArray createHexFrame(Command command, const QByteArray& data);

    // 私有化构造函数，防止外部直接创建实例
    CommunicationsProtocol(){}

    // 私有化拷贝构造和赋值操作，防止复制
    CommunicationsProtocol(const CommunicationsProtocol&) = delete;
    CommunicationsProtocol& operator=(const CommunicationsProtocol&) = delete;

  

};

#endif // COMMUNICATIONSPROTOCOL_H
