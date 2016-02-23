#include <QApplication>
#include "../include/mainwindow.h"
#include "../include/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
