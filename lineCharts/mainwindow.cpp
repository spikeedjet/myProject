#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QCursor>
#include <QLabel>
#include <QLegendMarker>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>
#include <QSplineSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    series->setPointsVisible(true); // Optional: Show points on the curve
    series->setUseOpenGL(true);     // Optional: Improve performance for large datasets
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

    // Set different colors for the series
    QPen pen1(Qt::red);
    series->setPen(pen1);

    QPen pen2(Qt::blue);
    series01->setPen(pen2);

    auto chart = new QChart;
    // Enable and configure the legend
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    // Add a title next to the legend
    auto legendTitle = new QGraphicsTextItem("Legend Title");
    QFont font;
    font.setBold(true);
    legendTitle->setFont(font);
    legendTitle->setDefaultTextColor(Qt::black);
  

    chart->addSeries(series);
    chart->addSeries(series01);
    chart->createDefaultAxes();
    chart->setTheme(QChart::QChart::ChartThemeLight);
    chart->setTitle("Simple Line Chart");

    // Customize legend markers
    for (QLegendMarker *marker : chart->legend()->markers()) {
        marker->setLabel(QString("%1").arg(marker->series()->name()));
        marker->setBrush(QBrush(Qt::yellow));
        marker->setPen(QPen(Qt::black));

        // Connect the clicked signal to toggle series visibility
        connect(marker, &QLegendMarker::clicked, this, [marker]() {
            auto series = marker->series();
            series->setVisible(!series->isVisible());
        });
    }

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [series01, chart]() {
        static int x = 24; // Start adding points after the last x value
        int y = QRandomGenerator::global()->bounded(10); // Generate random y value between 0 and 9
        series01->append(x, y);
        x += 2; // Increment x for the next point

        // Update chart axes to include the new point
        auto horizontalAxis = chart->axes(Qt::Horizontal).first();
        auto verticalAxis = chart->axes(Qt::Vertical).first();
        horizontalAxis->setRange(0, x);
        verticalAxis->setRange(0, 10);
    });
    timer->start(100); // Add a new point every second

    auto chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::NonCosmeticBrushPatterns);
    // Enable zooming and panning
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setMinimumSize(400,300);
    ui->verticalLayout->addWidget(chartView);

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

double MainWindow::calculateY(double x, double a = 20)
{
    return pow(x, 2.0/3.0) + 0.9 * sqrt(3.3 - x * x) * sin(a * M_PI * x);

}
