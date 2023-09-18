#include "mainwindow.h"
#include <QApplication>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#elif (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    HDC hdc = CreateDC(L"display", NULL, NULL, NULL);
    int ndpi = GetDeviceCaps(hdc, LOGPIXELSY);
    qputenv("QT_SCALE_FACTOR", QString::number(ndpi / 96.0).toUtf8());
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
   // QApplication::setQuitOnLastWindowClosed(false);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
