#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartview.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建自定义ChartView并添加到布局
    customChartView = new ChartView(this);
    ui->verticalLayout->addWidget(customChartView);

    // 可选：如果ChartView需要暴露label用于显示坐标，可以通过接口获取并添加
    QLabel* coordLabel = customChartView->coordLabel();
    if (coordLabel) {
        ui->verticalLayout->addWidget(coordLabel);
    }

    // 定时器：随着时间推移自动添加数据点
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        static qreal lastX = 25;
        lastX += 1;
        qreal newY = QRandomGenerator::global()->bounded(1, 10);
        customChartView->addDataPointToSeries01(QPointF(lastX, newY));
    });
    timer->start(50); // 每500ms添加一个点


    
    // 定时器：随着时间推移自动添加数据点
    QTimer *timerjava = new QTimer(this);
    connect(timerjava, &QTimer::timeout, this, [this]() {
        static qreal lastX = 25;
        lastX += 1;
        qreal newY = QRandomGenerator::global()->bounded(1, 10);
        customChartView->addDataPointToSeries(QPointF(lastX, newY));
    });
    timerjava->start(50); // 每500ms添加一个点
}

MainWindow::~MainWindow()
{
    delete ui;
}

