#include <QtTest/QtTest>
#include "../src/include/mainwindow.h"

class Test_MainWindow: public QObject
{
    Q_OBJECT
private slots:
private:
    MainWindow *testWindow;
};



}



QTEST_MAIN(Test_Database)
#include "test_mainwindow.moc"

