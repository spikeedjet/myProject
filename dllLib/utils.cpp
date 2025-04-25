#include "utils.h"
#include <QString>
#include <QDebug>

namespace Utils {

    quint16 calCheckSum(const QByteArray& frame) {
        quint32 sum = 0;
        constexpr int headerLength = 4;

        for (int i = headerLength; i < frame.size(); i++) {
            sum += static_cast<uint8_t>(frame[i]);
        }
        return sum & 0xFFFF;
    }

    QByteArray qint32ToQByteArray(qint32 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        // stream.setByteOrder(QDataStream::LittleEndian);
        stream << value;
        return data;
    }
    QByteArray quint32ToQByteArray(quint32 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        // stream.setByteOrder(QDataStream::LittleEndian);
        stream << value;
        return data;
    }

    QByteArray qint8ToQByteArray(qint8 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << value;
        return data;
    }
    QByteArray quint8ToQByteArray(quint8 value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << value;
        return data;
    }

    QByteArray floatToQByteArray(float value) {
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << value;
        return data;
    }

    //正解计算已知前进的位移x1,x2,x3 求高度z,旋转角度θx,θy
    void FK(double x1, double x2, double x3, double& z, double& thetaX, double& thetaY){

        //以最外侧为位移x的原点x不能小于θ

        // double z1 = x1 * tan(Theta);
        // double z2 = x2 * tan(Theta);
        // double z3 = x3 * tan(Theta);

        double z1 = x1 ;
        double z2 = x2 ;
        double z3 = x3 ;

        thetaX = asin((z1 - 0.5 * (z2 + z3)) / (L * 0.5 * sqrt(3)));
        thetaY = asin((z2 - z3) / L);
        z =(z1 + z2 + z3) / 3;
    }

    //反解计算 已知高度z,旋转弧度θxRAD,θyRAD，求前进的位移x1,x2,x3
    void IK(double z, double thetaX, double thetaY, double& x1, double& x2, double& x3){

        double L1 = L * 0.5 * sqrt(3);
        //根据等边三角形的边长计算高度

        //qDebug(）<< "L1 ="<< L1;

        double z3 = (3 * z - L1 * sin(thetaX) - 1.5 * L * sin(thetaY)) / 3;
        double z2 = z3 + L * sin(thetaY);
        double z1 = z3 + L1 * sin(thetaX) + 0.5 * L * sin(thetaY);

        // x1 = z1 / tan(Theta);
        // x2 = z2 / tan(Theta);
        // x3 = z3 / tan(Theta);
        x1 = z1 ;
        x2 = z2 ;
        x3 = z3 ;
    }


    //IK已知末端的位姿，求各个关节的移动距离
    QList<int> IK_flattenOut(double x, double y, double theta){

        //台面移动量 x y e（theta）
        //旋转中心 at，bt
        theta = theta *(M_PI / 180);//需要角度转换弧度

        // double ux = 117.5 * 1000000, uy = -117.5 * 1000000;
        // double vx = 117.5 * 1000000, vy = 117.5 * 1000000;
        // double wx = -117.5 * 1000000, wy = -117.5 * 1000000;
        double ux = 170 * 1000000, uy = 220 * 1000000;
        double vx = 220 * 1000000, vy = -170 * 1000000;
        double wx = -170 * 1000000, wy = -220 * 1000000;
        double at = 0, bt = 0;

        double su = (ux - at) * (sin(theta) * tan(theta) + cos (theta)) + (bt + y - uy) * tan (theta) + at + x - ux;
        double sv = (vy - bt) * (sin(theta) * tan(theta) + cos (theta)) + (vx -at - x) * tan (theta) + bt + y - vy;
        double sw = (wy - bt) * (sin(theta) * tan(theta) + cos (theta)) + (wx -at - x) * tan (theta) + bt + y - wy;

        QList<int> result(3);
        result[0] = static_cast<int>(su);
        result[1] = static_cast<int>(sv);
        result[2] = static_cast<int>(sw);
    
        return result;

    }

    qint32 byteArrayToInt32(const QByteArray& data) {
        // 检查数据长度并补足8字节
        QByteArray d = data;
        if (data.size() < 8) {
            d = data.rightJustified(8, '0');
        } else if (data.size() > 8) {
            qDebug() << "Error: Input data length must be 8 bytes or less, current length:" << data.size();
            return 0;
        }

        d = QByteArray::fromHex(data);

        QDataStream stream(d);
        qint32 result;
        stream >> result; // 读取 4 字节为 qint32
        return result;
    }




} // namespace Utils




