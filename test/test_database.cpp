#include <QtTest/QtTest>
#include "../src/include/database.h"
#include "trip.h"
#include "mainwindow.h"

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
    void testGetCartTotal();
    void testGetDistanceFromRestaurantByID();
    void testGetDistanceFromRestaurantByName();
    void testGetAllRestaurantIds();
    void testRouteDistance1();

private:
    Database *testDB;
    Trip *the_trip;
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

void Test_Database::testGetCartTotal()
{
//    QVERIFY(testDB->GetCartTotal() > 0);
}

void Test_Database::testGetDistanceFromRestaurantByID()
{
    QVector<double> testMap;
    testMap = testDB->GetRestaurantDistances(0);

    QVERIFY(testMap.contains(43824));
    QVERIFY(testMap.contains(18588));
    QVERIFY(testMap.contains(158));
    QVERIFY(testMap.contains(1234));

}
void Test_Database::testGetDistanceFromRestaurantByName()
{
    QVector<double> testMap;
    testMap = testDB->GetRestaurantDistances("Testaurant");

    QVERIFY(testMap.contains(43824));
    QVERIFY(testMap.contains(18588));
    QVERIFY(testMap.contains(158));
    QVERIFY(testMap.contains(1234));

}

void Test_Database::testGetAllRestaurantIds()
{
    QVector<int> testIds;
    testIds = testDB->GetAllRestaurantIds();
    QVERIFY(testIds.contains(0));
    QVERIFY(testIds.contains(1));
    QVERIFY(testIds.contains(2));
    QVERIFY(testIds.contains(3));
    QVERIFY(testIds.contains(4));
}


void Test_Database::testRouteDistance1()
{
    testDB->close();
    delete testDB;
    testDB = new Database("fast_food_restaurants",
                          "cs1d-fast-food-fantasy.cjv0rqkpv8ys.us-west-1.rds.amazonaws.com",
                          "dankdevz",
                          "cs1d-fast-food-fantasy");
    QVector<int> testVector;
    double ValidDist = 32.89;
    Trip *the_trip = new Trip(testDB);

    QVector<int> locations;
    locations.push_back(1);
    locations.push_back(2);
    locations.push_back(3);

    QVector<int> valid1;
    valid1.push_back(2);
    valid1.push_back(1);
    valid1.push_back(3);

    qDebug() << "Testing Route Algorith with Locations: " << locations;

    the_trip->findRouteBrute(locations);

    qDebug() << "TRIP DISTANCE: " << the_trip->getDistance()
             << " (should be " << ValidDist << ") WITH ROUTE:" << the_trip->getRoute();

    QCOMPARE(the_trip->getRoute(), valid1);
    QCOMPARE(the_trip->getDistance(), ValidDist);
}
//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Database)
#include "test_database.moc"
