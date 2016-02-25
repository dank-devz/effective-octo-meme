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
    //replace this with connection to test Database once we have it up and running.
    testDB = new Database("fast_food_restaurants_testing", "cs1d-fast-food-fantasy-testing.cjv0rqkpv8ys.us-west-1.rds.amazonaws.com",
                          "dankdevz", "dankdevz");
    QVERIFY(testDB != NULL);
}

void Test_Database::testOpen()
{
    QVERIFY(testDB->isOpen());
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

