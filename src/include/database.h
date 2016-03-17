#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QDebug>

/**
 * @brief The Database class is a wrapper for QSqlDatabase, with
 * many handy methods.
 */
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
    ///Add a restaurant
    bool AddRestaurant(QString restaurantName);
    ///Remove a restaurant
    bool RemoveRestaurant(int restaurantId);
    bool RemoveRestaurant(QString restaurantName);
    ///Add an item to purchases
    bool PurchaseItem(int itemId, int quantity, QString name, double price);
    ///Update quantity in cart
    bool UpdateQuantity(int quantity, int itemId);
    ///Clear cart
    bool ClearCart();
    ///Add new restaurant and all info
    bool AddNewRestaurant(QString restaurantName, QVector<QString> menuItemNames,
                          QVector<double> menuItemPrices, QVector<int> otherRestaurantIds,
                          QVector<double> distances);
    ///Add a new distance
    bool AddDistance(int from, int to, double distance);

    //Accessors
    ///Return a list of restaurants
    QList<QString> GetRestaurants();
    ///Retrieve a restaurant's unique ID
    int GetRestaurantId(QString restaurantName);
    ///Retrieve a restaurant's name given their ID
    QString GetRestaurantName(int id);
    ///Retrieve a menu item's unique ID
    int GetItemId(int restaurantId, QString itemName);
    ///Retrieve the total cost of the items in the cart.
    double GetCartTotal();
    ///Authenticate an Admin
    bool AuthenticateAdmin(QString username, QString password);

    /// Retrieve Restaurant Distances
    QVector<double> GetRestaurantDistances(QString name);
    /// Retrieve Restaurant Distances
    QVector<double> GetRestaurantDistances(int restaurantId);
    /// Retrieve Restaurant IDS
    QVector<int> GetAllRestaurantIds() const;
    /// Retrieve restaurant Names
    QVector<QString> GetAllRestaurantNames() const;

    /// Shopping Cart Methods
    QList<QString> 	GetRestaurantMenuItemNames(int restaurantId);

    /// Gets the price of an item given the itemId
    double 			GetItemPrice(int itemId);
    double 			GetItemPrice(QString itemName);

private:

};

#endif // DATABASE_H
