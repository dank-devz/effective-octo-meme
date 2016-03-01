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
    void testValidAddMenuItem();
    void testInvalidAddMenuItem();
    void testRemoveMenuItem();
    void testGetDistanceFromRestaurant();
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

void Test_Database::testValidAddMenuItem()
{
    QVERIFY(testDB->AddMenuItem(0, "Spicy Tuna Roll", 4.50));
}

void Test_Database::testInvalidAddMenuItem()
{
    QVERIFY(!testDB->AddMenuItem(420, "Special Brownie", 4.20));
}

void Test_Database::testRemoveMenuItem()
{
    QVERIFY(testDB->RemoveMenuItem(0, "Spicy Tuna Roll"));
}

void Test_Database::testGetDistanceFromRestaurant()
{
    QList<double> testMap;
    testMap = testDB->GetRestaurantDistances("Testaurant");

    QVERIFY(testMap.contains(43824));
    QVERIFY(testMap.contains(8080));
    QVERIFY(testMap.contains(199));
    QVERIFY(testMap.contains(518));
    QVERIFY(testMap.contains(4888));
    QVERIFY(testMap.contains(18588));
    QVERIFY(testMap.contains(9000));
    QVERIFY(testMap.contains(4567));
    QVERIFY(testMap.contains(1234));

}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

