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
    void testAddRestaurant();
    void testRemoveRestaurant();
    void testGetItemId();
    void testGetRestaurants();
    void testGetCartTotal();
    void testGetDistanceFromRestaurantByID();
    void testGetDistanceFromRestaurantByName();
    void testGetAllRestaurantIds();

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

void Test_Database::testAddRestaurant()
{
    QVERIFY(testDB->AddRestaurant("Bobby's"));
}

void Test_Database::testRemoveRestaurant()
{
    QVERIFY(testDB->RemoveRestaurant("Bobby's"));
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


void Test_Database::testGetCartTotal()
{
    QVERIFY(testDB->GetCartTotal() > 0);
}

void Test_Database::testGetDistanceFromRestaurantByID()
{
    QList<double> testMap;
    testMap = testDB->GetRestaurantDistances(0);

    QVERIFY(testMap.contains(43824));
    QVERIFY(testMap.contains(18588));
    QVERIFY(testMap.contains(158));
    QVERIFY(testMap.contains(1234));

}
void Test_Database::testGetDistanceFromRestaurantByName()
{
    QList<double> testMap;
    testMap = testDB->GetRestaurantDistances("Testaurant");

    QVERIFY(testMap.contains(43824));
    QVERIFY(testMap.contains(18588));
    QVERIFY(testMap.contains(158));
    QVERIFY(testMap.contains(1234));

}

void Test_Database::testGetAllRestaurantIds()
{
    QList<int> testIds;
    testIds = testDB->GetAllRestaurantIds();
    QVERIFY(testIds.contains(0));
    QVERIFY(testIds.contains(1));
    QVERIFY(testIds.contains(2));
    QVERIFY(testIds.contains(3));
    QVERIFY(testIds.contains(4));
}


//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"
