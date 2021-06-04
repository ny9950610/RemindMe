#include "headers/mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icon.png"));
    a.setQuitOnLastWindowClosed(false);

    MainWindow w;
    w.show();
    return a.exec();
}
