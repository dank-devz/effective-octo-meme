#include "../include/mainwindow.h"
#include <QApplication>
#include "../include/database.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Database *db = new Database();

    w.show();


    return a.exec();
}
