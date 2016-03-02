#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QDebug>


class Database : public QSqlDatabase
{
public:

    ///Create database from specified db file and driver
    Database(QString databaseName, QString hostname, QString username, QString password);

    ///Destructor
    ~Database();

    //Mutators
    ///Add an item to a specified restaurant's menu.
    bool AddMenuItem(int restaurantId, QString itemName, double price);
    ///Remove an item from a specified restaurant's menu.
    bool RemoveMenuItem(int restaurantId, QString itemName);
    ///Add an item to purchases
    bool PurchaseItem(int itemId, int quantity);

    //Accessors
    ///Return a list of restaurants
    QList<QString> GetRestaurants();
    ///Retrieve a restaurant's unique ID
    int GetRestaurantId(QString restaurantName);
    ///Retrieve a menu item's unique ID
    int GetItemId(int restaurantId, QString itemName);
    ///Retrieve the total cost of the items in the cart.
    double GetCartTotal();

    /// Retrieve Restaurant Distances
    QList<double> GetRestaurantDistances(QString name);

    /// Retrieve Restaurant Distances
    QList<double> GetRestaurantDistances(int restaurantId);

    /// Retrieve Restaurant IDS
    QList<int> GetAllRestaurantIds() const;

    /// Shopping Cart Methods
    QList<QString> 	GetRestaurantMenuItemNames(int restaurantId);

    /// Gets the price of an item given the itemId
    double 			GetItemPrice(int itemId);
    double 			GetItemPrice(QString itemName);

private:
};

#endif // DATABASE_H
