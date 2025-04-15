#include "widget.h"
#include "ui_widget.h"
#include <QtConcurrent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<"Main thread:"<<QThread::currentThreadId();

    //运行任务
    QFuture<void> future = QtConcurrent::run([this]() { simpleTask(42); });

    //等待任务完成
    future.waitForFinished();
    qDebug()<<"Task finished";

}

Widget::~Widget()
{
    delete ui;
}

void Widget::simpleTask(int value)
{
    qDebug()<<"Task running with value:" << value <<"in thread:"<<QThread::currentThreadId();
    QThread::sleep(5); //模拟耗时操作
}
