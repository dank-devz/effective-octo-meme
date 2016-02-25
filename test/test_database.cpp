#include <QtTest/QtTest>
#include "../src/include/database.h"

class Test_Database: public QObject
{
    Q_OBJECT
//public:
//    Test_Database();
//    ~Test_Database();
private slots:
    void initTest();
    void testOpen();
private:
    Database *testDB;
};

void Test_Database::initTest(){
    testDB = new Database();
}

void Test_Database::testOpen()
{
    QVERIFY(testDB->isOpen());
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

