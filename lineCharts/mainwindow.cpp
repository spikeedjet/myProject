#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chartview.h"

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QCursor>
#include <QLabel>
#include <QLegendMarker>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>
#include <QSplineSeries>
#include <QColorDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //series
    auto series = new  QSplineSeries;
    series->append(0,6);
    series->append(2,4);
    series->append(3,8);
    series->append(7,4);
    series->append(10,5);
    series->append(15,6);
    series->append(18,4);
    series->append(23,8);
    series->setName("java");
    series->setPointsVisible(true);
    series->setUseOpenGL(true);
    series->setPen(QPen(Qt::red));
    series->setPointsVisible(true);

    auto series01 = new  QSplineSeries;
    series01->append(0,2);
    series01->append(2,2);
    series01->append(3,3);
    series01->append(7,4);
    series01->append(10,5);
    series01->append(15,5);
    series01->append(18,4);
    series01->append(23,1);
    series01->setName("c++");
    series01->setPointsVisible(true);
    series01->setUseOpenGL(true);
    series01->setPen(QPen(Qt::red));
    series01->setPointsVisible(true);

    QPen pen1(Qt::red);
    series->setPen(pen1);

    QPen pen2(Qt::blue);
    series01->setPen(pen2);

   


    //chart
    auto chart = new QChart;
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->addSeries(series);
    chart->addSeries(series01);
    chart->createDefaultAxes();

    

    //更改曲线颜色
    for (QLegendMarker* marker : chart->legend()->markers()) {
        // Connect to marker's clicked signal
        connect(marker, &QLegendMarker::clicked, this, [this, marker]() {
            QColor newColor = selectColor();
            if (newColor.isValid()) {
                QAbstractSeries* series = marker->series();
                // Update the line color
                if (auto lineSeries = qobject_cast<QSplineSeries*>(series)) {
                    QPen pen = lineSeries->pen();
                    pen.setColor(newColor);
                    lineSeries->setPen(pen);
                }
            }
        });
    }
    chart->setTheme(QChart::QChart::ChartThemeLight);
    chart->setTitle("Simple Line Chart");



    //chartview
    auto customChartView = new ChartView;
    customChartView->setChart(chart);
    customChartView->setRenderHints(QPainter::NonCosmeticBrushPatterns | QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 添加抗锯齿
    customChartView->setMinimumSize(400,300);
    ui->verticalLayout->addWidget(customChartView);




    // Add QLabel to display coordinates
    auto coordLabel = new QLabel(this);
    coordLabel->setStyleSheet("QLabel { background-color : white; }");
    coordLabel->setAlignment(Qt::AlignCenter);
    ui->verticalLayout->addWidget(coordLabel);
    // Connect the hovered signal to update the QLabel
    connect(series, &QLineSeries::hovered, this, [coordLabel](const QPointF &point, bool state) {
        if (state) {
            coordLabel->setText(QString("X: %1, Y: %2").arg(point.x()).arg(point.y()));
        } else {
            coordLabel->clear();
        }
    });
    connect(series01, &QLineSeries::hovered, this, [coordLabel](const QPointF &point, bool state) {
        if (state) {
            coordLabel->setText(QString("X: %1, Y: %2").arg(point.x()).arg(point.y()));
        } else {
            coordLabel->clear();
        }
    });




}


MainWindow::~MainWindow()
{
    delete ui;
}

QColor MainWindow::selectColor()
{
    auto color =  QColorDialog::getColor();
    return color;
}

