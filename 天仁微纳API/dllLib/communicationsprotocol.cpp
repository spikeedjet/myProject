#include "communicationsprotocol.h"

#include <stdexcept>
#include <QtCore/QByteArray>
#include "utils.h"

using namespace Utils;

CommunicationsProtocol* CommunicationsProtocol::m_instance = nullptr;

QByteArray CommunicationsProtocol::createHexFrame(Command command, const QByteArray& data)
{
    // 计算数据长度: 命令长度(2) + 状态(1) + 数据长度 + CRC(2)
    uint16_t dataLength = 2 + 1 + data.size() + 2;

    QByteArray frame;

    frame.append('\x7F');
    frame.append('\xC0');
    frame.append('\x00');
    frame.append('\x01');

    frame.append((dataLength >> 8) & 0xFF);
    frame.append(dataLength & 0xFF);
    frame.append(static_cast<char>(command));
    frame.append(data);

    // 计算校验和
    uint16_t checksum =calCheckSum(frame);
    frame.append(static_cast<char>((checksum >> 8) & 0xFF));
    frame.append(static_cast<char>(checksum & 0xFF));

    return frame;
}

QByteArray CommunicationsProtocol::handshake()
{
    return createHexFrame(Command::HANDSHAKE, QByteArray());
}

QByteArray CommunicationsProtocol::requestData()
{
    return createHexFrame(Command::REQUEST_DATA, QByteArray());
}

QByteArray CommunicationsProtocol::setStreamingMode(bool enable)
{
    QByteArray data;
    data.append(enable ? 0x01 : static_cast<char>(0x00));
    data.append(static_cast<char>(0x00));
    data.append(static_cast<char>(0x00));
    return createHexFrame(Command::SET_STREAMING_MODE, data);
}


QByteArray CommunicationsProtocol::stopMotion(quint8 stopType)
{
    if (stopType != 0x00 && stopType != 0x01) {
        throw std::invalid_argument("停止类型必须是 0x00 或 0x01");
    }
    QByteArray data;
    data.append(0xFF);
    data.append(stopType);
    return createHexFrame(Command::STOP_MOTION, data);
}

QByteArray CommunicationsProtocol::findZeroing()
{
    QByteArray data;
    data.append(0x01);
    data.append(static_cast<char>(0x00));
    return createHexFrame(Command::ZERO_POSITION, data);
}

QByteArray CommunicationsProtocol::singleAxisMotionWithInt(quint8 dataTypeAxis, qint32 position)
{
    /* 单轴运动控制
     Args:
     data_type_axis (QByteArray): 轴数据格式和编号
     - bit7: 数据格式 (0:int, 1:float)
     - bit6-0: 轴编号(1-6)

     int类型轴编号:
     - 0x01: 轴1
     - 0x02: 轴2
     - 0x04: 轴3
     - 0x08: 轴4
     - 0x10: 轴5
     - 0x20: 轴6

     float类型轴编号:
     - 0x81: 轴1
     - 0x82: 轴2
     - 0x84: 轴3
     - 0x88: 轴4
     - 0x90: 轴5
     - 0xA0: 轴6

     position (c_int32): 目标位置值

     Returns:
     QByteArray: 编码后的通信帧 */

    QByteArray data;
    data.append(dataTypeAxis);

    data.append(qint32ToQByteArray(position));

    return createHexFrame(Command::SINGLE_AXIS_MOTION, data);
}

QByteArray CommunicationsProtocol::singleAxisMotionWithFloat(quint8 dataTypeAxis, float position)
{
    QByteArray data;
    data.append(dataTypeAxis);

    data.append(floatToQByteArray(position));

    return createHexFrame(Command::SINGLE_AXIS_MOTION, data);
}

QByteArray CommunicationsProtocol::multiAxisMotion(quint8 axisNumber, qint32 axis1Position, qint32 axis2Position,
                                                   qint32 axis3Position, qint32 axis4Position, qint32 axis5Position,
                                                   qint32 axis6Position)
{
    QByteArray data;
    data.append(axisNumber);
    data.append(qint32ToQByteArray(axis1Position));
    data.append(qint32ToQByteArray(axis2Position));
    data.append(qint32ToQByteArray(axis3Position));
    data.append(qint32ToQByteArray(axis4Position));
    data.append(qint32ToQByteArray(axis5Position));
    data.append(qint32ToQByteArray(axis6Position));
    return createHexFrame(Command::MULTI_AXIS_MOTION, data);
}

QByteArray CommunicationsProtocol::sendInterferometerAxisData(qint32 axis1, qint32 axis2, qint32 axis3)
{
    QByteArray data;
    data.append(qint32ToQByteArray(axis1));
    data.append(qint32ToQByteArray(axis2));
    data.append(qint32ToQByteArray(axis3));

    return createHexFrame(Command::REQUEST_DATA,data);

}

QByteArray CommunicationsProtocol::jienshiCloseLoop(qint8 mode, qint8 speedFlag, qint32 speedValue, qint8 noUseByte)
{
    /*  mode:
        0：关闭
        1：开启
    */
    QByteArray data;
    data.append(mode);
    data.append(speedFlag);
    data.append(qint32ToQByteArray(speedValue));
    data.append(qint32ToQByteArray(noUseByte));
    return createHexFrame(Command::JIENSHI_CLOSE_LOOP,data);
}
