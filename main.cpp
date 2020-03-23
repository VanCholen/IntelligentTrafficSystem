#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    CholenMap w;
//    SerialPortAssistant w;
    w.show();

    return a.exec();
}
