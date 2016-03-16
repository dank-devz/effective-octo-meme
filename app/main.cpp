#include "include/mainwindow.h"
#include <QApplication>
#include "include/database.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/qss/darkgreen.qss");
       if(file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           a.setStyleSheet(file.readAll());
           file.close();
       }

    MainWindow w;

    w.show();

    return a.exec();
}
