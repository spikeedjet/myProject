#include "dlllib.h"
#include <QDebug>

DllLib::DllLib() {}


//测试函数的定义
int DllLib::test()
{
    int num=10;
    qDebug()<<"动态库里面函数的输出num："<<num;
    return num;
}
