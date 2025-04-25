#pragma once
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <cmath>

#include <QEventLoop>
#include <QTimer>


namespace Utils {

    constexpr double L = 394.04 * 1000 * 1000;
    // constexpr double Theta = 14.04 * (M_PI / 180);

    quint16 calCheckSum(const QByteArray& frame);
    QByteArray qint32ToQByteArray(qint32 value);
    QByteArray quint32ToQByteArray(quint32 value);

    QByteArray qint8ToQByteArray(qint8 value);
    QByteArray quint8ToQByteArray(quint8 value);

    QByteArray floatToQByteArray(float value);

    void FK(double xl, double x2, double x3, double& z, double& thetaX, double& thetaY);
    void IK(double z, double thetaX, double thetaY, double& x1, double& x2, double& x3);
    QList<int> IK_flattenOut(double x, double y, double theta);


    qint32 byteArrayToInt32(const QByteArray& data);

    void mySleep(int ms) ;



}
