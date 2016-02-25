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
private:
    Database *testDB;
};

void Test_Database::initTest(){
    QVERIFY("Testing" == "Testing");
    testDB = new Database();
    QVERIFY(testDB->isOpen());
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

