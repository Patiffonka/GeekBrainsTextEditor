#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DontShowIconsInMenus);
    MainWindow w;
    w.show();
    return a.exec();
}
