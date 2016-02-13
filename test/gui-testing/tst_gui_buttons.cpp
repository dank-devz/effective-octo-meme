#include <QString>
#include <QtTest>

class gui_buttons : public QObject
{
    Q_OBJECT

public:
    gui_buttons();

private Q_SLOTS:
    void testCase1();
};

gui_buttons::gui_buttons()
{
}

void gui_buttons::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(gui_buttons)

#include "tst_gui_buttons.moc"
