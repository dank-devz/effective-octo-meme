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
    void testGetRestaurantId();
    void testGetItemId();
    void testGetRestaurants();
private:
    Database *testDB;
};

void Test_Database::initTest(){
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

void Test_Database::testGetRestaurantId()
{
    QVERIFY(testDB->GetRestaurantId("Testaurant") == 0);
}

void Test_Database::testGetItemId()
{
    QVERIFY(testDB->GetItemId(0, "Gizzards") == 1);
}

void Test_Database::testGetRestaurants()
{
    QList<QString> testList = testDB->GetRestaurants();
    QVERIFY(testList.size() > 0);
}



//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"

