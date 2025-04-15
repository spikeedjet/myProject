#include "mainwindow.h"

#include <QApplication>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;
//     engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//     return app.exec();
// }
