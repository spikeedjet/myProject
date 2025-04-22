#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>

class ChartView : public QChartView {
protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            lastPos = event->pos();
            isPanning = true;
            setCursor(Qt::ClosedHandCursor);
        }
        QChartView::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            isPanning = false;
            setCursor(Qt::ArrowCursor);
        }
        QChartView::mouseReleaseEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (isPanning) {
            QPointF delta = (event->pos() - lastPos);
            chart()->scroll(-delta.x(), delta.y());
            lastPos = event->pos();
        }

        // Update crosshair
        QPointF chartPos = chart()->mapToValue(event->pos());
        if (crosshairX) crosshairX->setPos(QPointF(chartPos.x(), 0));
        if (crosshairY) crosshairY->setPos(QPointF(0, chartPos.y()));

        QChartView::mouseMoveEvent(event);
    }

    void wheelEvent(QWheelEvent *event) override {
        qreal factor = event->angleDelta().y() > 0 ? 0.9 : 1.1;
        QRectF rect = chart()->plotArea();
        QPointF center = rect.center();
        rect.setSize(rect.size() * factor);
        QPointF newCenter = rect.center();
        QPointF offset = newCenter - center;
        chart()->zoomIn(rect.adjusted(-offset.x(), -offset.y(), -offset.x(), -offset.y()));
        QChartView::wheelEvent(event);
    }

    void showEvent(QShowEvent *event) override {
        // Initialize crosshair lines
        if (!crosshairX) {
            crosshairX = new QGraphicsLineItem(chart());
            crosshairX->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            crosshairY = new QGraphicsLineItem(chart());
            crosshairY->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            updateCrosshair();
        }
        QChartView::showEvent(event);
    }

    void resizeEvent(QResizeEvent *event) override {
        QChartView::resizeEvent(event);
        updateCrosshair();
    }

private:
    QPoint lastPos;
    bool isPanning = false;
    QGraphicsLineItem *crosshairX = nullptr;
    QGraphicsLineItem *crosshairY = nullptr;

    void updateCrosshair() {
        if (crosshairX && crosshairY) {
            QRectF plotArea = chart()->plotArea();
            crosshairX->setLine(plotArea.left(), 0, plotArea.right(), 0);
            crosshairY->setLine(0, plotArea.top(), 0, plotArea.bottom());
        }
    }
};

#endif // CHARTVIEW_H
