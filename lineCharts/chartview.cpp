#include "chartview.h"
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QtMath>

#define UPDATE_THRESHOLD 1

ChartView::ChartView(QWidget *parent)
    : QChartView(parent)
{
    setupSeries();
    setupChart();
    setupLegend();
    setupCoordLabel();

    setChart(chart);
    setRenderHints(QPainter::NonCosmeticBrushPatterns | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setMinimumSize(400, 300);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    
}

void ChartView::setupSeries()
{
    series = new QSplineSeries;
    series->setName("java");
    series->setPointsVisible(true);
    series->setUseOpenGL(true);
    series->setPen(QPen(Qt::red));

     // Store initial points
    for (int i = 0; i < series->count(); ++i) {
        dataPointsjava.append(series->at(i));
    }
    // 确保初始显示
    series->replace(dataPointsjava);

    series01 = new QSplineSeries;
   
    series01->setName("c++");
    series01->setUseOpenGL(true);
    series01->setPointsVisible(false);
    series01->setPen(QPen(Qt::blue));

    // Store initial points
    for (int i = 0; i < series01->count(); ++i) {
        dataPoints.append(series01->at(i));
    }
    // 确保初始显示
    series01->replace(dataPoints);
}

// 新增：通过方法添加数据点并自动更新图像
void ChartView::addDataPointToSeries(const QPointF &point)
{
    QMutexLocker locker(&dataLock);
    dataPointsjava.append(point);
    if (dataPointsjava.size() >= 100) {
        dataPointsjava.clear();
    }
    series->replace(dataPointsjava);

    // 自动调整Y轴范围以适应所有数据点
    if (auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first())) {
        if (!dataPointsjava.isEmpty()) {
            qreal minY = dataPointsjava.first().y();
            qreal maxY = dataPointsjava.first().y();
            for (const QPointF& pt : dataPointsjava) {
                if (pt.y() < minY) minY = pt.y();
                if (pt.y() > maxY) maxY = pt.y();
            }
            if (minY == maxY) {
                minY -= 1;
                maxY += 1;
            }
            axisY->setRange(minY-2, maxY+2);
        }
    }
    if (auto axisX = qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first())) {
        if (!dataPointsjava.isEmpty())
            axisX->setRange(dataPointsjava.first().x(), dataPointsjava.last().x());
    }
    chart->update();
}
// 新增：通过方法添加数据点并自动更新图像
void ChartView::addDataPointToSeries01(const QPointF &point)
{
    QMutexLocker locker(&dataLock);
    dataPoints.append(point);
    if (dataPoints.size() >= 100) {
        dataPoints.clear();
    }
    series01->replace(dataPoints);

    // 自动调整Y轴范围以适应所有数据点
    if (auto axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first())) {
        if (!dataPoints.isEmpty()) {
            qreal minY = dataPoints.first().y();
            qreal maxY = dataPoints.first().y();
            for (const QPointF& pt : dataPoints) {
                if (pt.y() < minY) minY = pt.y();
                if (pt.y() > maxY) maxY = pt.y();
            }
            if (minY == maxY) {
                minY -= 1;
                maxY += 1;
            }
            axisY->setRange(minY-2, maxY+2);
        }
    }
    if (auto axisX = qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first())) {
        if (!dataPoints.isEmpty())
            axisX->setRange(dataPoints.first().x(), dataPoints.last().x());
    }
    chart->update();
}



void ChartView::setupChart()
{
    chart = new QChart;
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->addSeries(series);
    chart->addSeries(series01);
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setTitle("Simple Line Chart");
}

void ChartView::setupLegend()
{
    for (QLegendMarker* marker : chart->legend()->markers()) {
        connect(marker, &QLegendMarker::clicked, this, [this, marker]() {
            QColor newColor = selectColor();
            if (newColor.isValid()) {
                auto s = marker->series();
                if (auto lineSeries = qobject_cast<QSplineSeries*>(s)) {
                    QPen pen = lineSeries->pen();
                    pen.setColor(newColor);
                    lineSeries->setPen(pen);
                }
            }
        });
    }
}

void ChartView::setupCoordLabel()
{
    m_coordLabel = new QLabel(this);
    m_coordLabel->setStyleSheet("QLabel { background-color : white; }");
    m_coordLabel->setAlignment(Qt::AlignCenter);

    connect(series, &QLineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            m_coordLabel->setText(QString("X: %1, Y: %2").arg(point.x()).arg(point.y()));
        } else {
            m_coordLabel->clear();
        }
    });
    connect(series01, &QLineSeries::hovered, this, [this](const QPointF &point, bool state) {
        if (state) {
            m_coordLabel->setText(QString("X: %1, Y: %2").arg(point.x()).arg(point.y()));
        } else {
            m_coordLabel->clear();
        }
    });
}

QColor ChartView::selectColor()
{
    return QColorDialog::getColor(Qt::white, this, "选择颜色");
}


// 鼠标事件和十字线
void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPos = event->pos();
        isPanning = true;
        setCursor(Qt::ClosedHandCursor);
    }
    QChartView::mousePressEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
    QChartView::mouseReleaseEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (isPanning) {
        QPointF delta = (event->pos() - lastPos);
        chart->scroll(-delta.x(), delta.y());
        lastPos = event->pos();
    }
    // 十字线
    QPointF chartPos = chart->mapToValue(event->pos());
    if (crosshairX) crosshairX->setPos(QPointF(chartPos.x(), 0));
    if (crosshairY) crosshairY->setPos(QPointF(0, chartPos.y()));
    QChartView::mouseMoveEvent(event);
}

void ChartView::wheelEvent(QWheelEvent *event)
{
    qreal factor = event->angleDelta().y() > 0 ? 0.9 : 1.1;
    QRectF rect = chart->plotArea();
    QPointF center = rect.center();
    rect.setSize(rect.size() * factor);
    QPointF newCenter = rect.center();
    QPointF offset = newCenter - center;
    chart->zoomIn(rect.adjusted(-offset.x(), -offset.y(), -offset.x(), -offset.y()));
    QChartView::wheelEvent(event);
}

void ChartView::showEvent(QShowEvent *event)
{
    if (!crosshairX) {
        crosshairX = new QGraphicsLineItem(chart);
        crosshairX->setPen(QPen(Qt::gray, 1, Qt::DashLine));
        crosshairY = new QGraphicsLineItem(chart);
        crosshairY->setPen(QPen(Qt::gray, 1, Qt::DashLine));
        updateCrosshair();
    }
    QChartView::showEvent(event);
}

void ChartView::resizeEvent(QResizeEvent *event)
{
    QChartView::resizeEvent(event);
    updateCrosshair();
}

void ChartView::updateCrosshair()
{
    if (crosshairX && crosshairY) {
        QRectF plotArea = chart->plotArea();
        crosshairX->setLine(plotArea.left(), 0, plotArea.right(), 0);
        crosshairY->setLine(0, plotArea.top(), 0, plotArea.bottom());
    }
}
