#include <QtTest/QtTest>

class Test_Database: public QObject
{
    Q_OBJECT
//public:
//    Test_Database();
//    ~Test_Database();
private slots:
    void initTest();
};

void Test_Database::initTest(){
    QVERIFY("Testing" == "Testing");
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

