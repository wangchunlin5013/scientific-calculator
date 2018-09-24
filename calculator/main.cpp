#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calculationexpression.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    CalculationExpression clc;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QString("clc"),&clc);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
