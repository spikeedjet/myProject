#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QMutex>
#include "chartview.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();





private:
    Ui::MainWindow *ui;
    QTimer *updateTimer;
    QSplineSeries *series01;
    QVector<QPointF> dataPoints;
    QChart *chart;
    QMutex dataLock;
    int updateCounter = 0;
    const int UPDATE_THRESHOLD = 5; // Update chart every 5 data points
    ChartView *customChartView;
};
#endif // MAINWINDOW_H
