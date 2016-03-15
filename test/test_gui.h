#ifndef TEST_GUI_H
#define TEST_GUI_H
#include <QtTest>
#include "../src/include/mainwindow.h"

class Test_Gui: public QObject
{
    Q_OBJECT

private slots:
    void initGuiTest();

private:
    QMainWindow *testUI;
};

void Test_Gui::initGuiTest()
{
    QVERIFY("Gui INIT Testing" == "Gui INIT Testing");
}

#endif // TEST_GUI_H
