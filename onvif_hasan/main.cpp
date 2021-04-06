#include "mainwindow_onvif.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_onvif w;
    w.show();

    return a.exec();
}
