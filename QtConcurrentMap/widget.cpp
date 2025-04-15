#include "widget.h"
#include "ui_widget.h"
#include <QtConcurrent>
#include <QDebug>
#include <QCoreApplication>
#include <QList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QList<int> numbers = {1,2,3,4,5};
    qDebug()<<"Main thread:"<<QThread::currentThreadId();
    QFuture<void> future = QtConcurrent::map(numbers, [this](int &number) { processNumber(number); });
    future.waitForFinished();
    qDebug()<<"Results:"<<numbers;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::processNumber(int &number)
{
    //模拟处理
    number *= 2;
    qDebug() << "Processing" << number << "in thread:" << QThread::currentThreadId();
}
