#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent> // Include for QGraphicsSceneMouseEvent

// 自定义图形项，继承 QGraphicsItem
class CustomItem : public QGraphicsItem {
public:
    enum ShapeType { Rectangle, Circle };

    CustomItem(ShapeType type, qreal x, qreal y, qreal size, QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent), m_type(type), m_size(size) {
        setPos(x, y);
        setFlag(QGraphicsItem::ItemIsMovable); // 允许鼠标拖动
        setFlag(QGraphicsItem::ItemSendsGeometryChanges); // 检测位置变化
        m_color = Qt::blue; // 默认颜色
    }

    // 实现 boundingRect，必须提供绘制区域
    QRectF boundingRect() const override {
        return QRectF(-m_size / 2, -m_size / 2, m_size, m_size);
    }

    // 实现 shape，用于精确碰撞检测
    QPainterPath shape() const override {
        QPainterPath path;
        if (m_type == Rectangle) {
            path.addRect(boundingRect());
        } else {
            path.addEllipse(boundingRect());
        }
        return path;
    }

    // 绘制图形项
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override {
        painter->setBrush(m_color);
        painter->setPen(Qt::black);
        if (m_type == Rectangle) {
            painter->drawRect(boundingRect());
        } else {
            painter->drawEllipse(boundingRect());
        }
    }

    // 检测碰撞并更新颜色
    void checkCollision(QGraphicsScene *scene) {
        // 获取场景中所有与当前项碰撞的项
        QList<QGraphicsItem *> colliding = collidingItems(Qt::IntersectsItemShape);
        if (!colliding.isEmpty()) {
            m_color = Qt::red; // 碰撞时变红
            qDebug() << "Collision detected!";
        } else {
            m_color = Qt::blue; // 无碰撞时恢复蓝色
        }
        update(); // 触发重绘
    }

protected:
    // 位置变化时触发碰撞检测
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionHasChanged && scene()) {
            checkCollision(scene());
        }
        return QGraphicsItem::itemChange(change, value);
    }

private:
    ShapeType m_type;
    qreal m_size;
    QColor m_color;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // 添加两个图形项：矩形和圆形
    CustomItem *rect = new CustomItem(CustomItem::Rectangle, -50, 0, 200);
    CustomItem *circle = new CustomItem(CustomItem::Circle, 50, 0, 100);
    scene->addItem(rect);
    scene->addItem(circle);
}

MainWindow::~MainWindow()
{
    delete ui;
}
