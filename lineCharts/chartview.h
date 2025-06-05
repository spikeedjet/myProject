#pragma once

#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QValueAxis>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include <QColorDialog>



class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = nullptr);
    QLabel* coordLabel() const { return m_coordLabel; }
    void addDataPointToSeries01(const QPointF &point);
    void addDataPointToSeries(const QPointF &point);



protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;



private:
    QColor selectColor();
    void setupChart();
    void setupLegend();
    void setupSeries();
    void setupCoordLabel();
    void updateCrosshair();


    QSplineSeries *series = nullptr;
    QSplineSeries *series01 = nullptr;
    QChart *chart = nullptr;
    QLabel *m_coordLabel = nullptr;
    QTimer *updateTimer = nullptr;
    QVector<QPointF> dataPointsjava;
    QVector<QPointF> dataPoints;
    int updateCounter = 0;
    QMutex dataLock;

    // Crosshair
    QGraphicsLineItem *crosshairX = nullptr;
    QGraphicsLineItem *crosshairY = nullptr;
    QPoint lastPos;
    bool isPanning = false;
};
