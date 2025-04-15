#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QVBoxLayout>

#include <QQuickWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

}

MainWindow::~MainWindow()
{
    delete ui;
}
