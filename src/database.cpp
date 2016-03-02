#include "include/database.h"

/*!
 * \brief Database::Database
 * \param path path to sql database file
 */
Database::Database(QString databaseName, QString hostName, QString userName, QString password) : QSqlDatabase(addDatabase("QMYSQL"))
{
    setDatabaseName(databaseName);
    setHostName(hostName);
    setUserName(userName);
    setPassword(password);
    if(!open())
    {
        qDebug() << "Database error occurred";
        qDebug() << lastError();
    }
    else
    {
        qDebug() << "CONNECTED! Huzzah.";
    }

    //  query = QSqlQuery(*this);
    //  query.exec("PRAGMA foreign_keys = ON;");
}

/*!
 * \brief Database::~Database destructor
 */
Database::~Database()
{
    //  if(query.isActive())
    //  {
    //    query.finish();
    //    query.clear();
    //  }
    //  close();
}

/*
 * M U T A T O R S
 */

/**
 * @brief Database::AddMenuItem Add a menu item to the items table.
 * @param restaurantId Id of the restaurant this menu item belongs to.
 * @param itemName the name of the food item.
 * @param price the price of the food item.
 * @return true if record successfully added to items table
 */
bool Database::AddMenuItem(int restaurantId, QString itemName, double price)
{
    QSqlQuery query;

    //prepare a SQL query with named binding
    query.prepare("INSERT INTO items (id, name, price) "
                  "VALUES (:id, :name, :price)");

    //bind values
    query.bindValue(":id", restaurantId);
    query.bindValue(":name", itemName);
    query.bindValue(":price", price);

    return query.exec();
}

/**
 * @brief Database::RemoveMenuItem Remove an item from a restaurant's menu.
 * @param restaurantId the id of the restaurant to remove from.
 * @param itemName the name of the item to remove.
 * @return true if item is successfully removed from table.
 */
bool Database::RemoveMenuItem(int restaurantId, QString itemName)
{
    QSqlQuery query;

    //prepare a SQL query with named binding
    query.prepare("DELETE FROM items WHERE id = :id "
                  "and name = :name");

    //bind values
    query.bindValue(":id", restaurantId);
    query.bindValue(":name", itemName);

    return query.exec();
}

/**
 * @brief Database::GetRestaurants Return a list of restaurants
 * @return QList of QStrings of restaurant names
 */
QList<QString> Database::GetRestaurants()
{
    QList<QString> restaurantList;
    QSqlQuery query;
    if(query.exec("SELECT name from restaurants WHERE restaurants.id != 0"))
    {
        while(query.next())
        {
            restaurantList.append(query.value("name").toString());
        }
    }
    else
    {
        qDebug() << this->lastError().text();
    }
    return restaurantList;
}

/**
 * @brief Database::GetRestaurantId Retrieve a restaurant's unique ID given its name
 * @param restaurantName
 * @return -1 if failed, otherwise return restaurant ID
 */
int Database::GetRestaurantId(QString restaurantName)
{
    QSqlQuery query;

    query.prepare("SELECT id from restaurants where name = :restaurantName");
    query.bindValue(":restaurantName", restaurantName);
    if(query.exec()){
        if(query.next()){
            return query.value("id").toInt();
        }
        else
        {
            qDebug() << "No restaurant with that name exists.";
        }
    }
    else
    {
        qDebug() << lastError().text();
        return -1;
    }
}

/**
 * @brief Database::GetItemId Retrieve a menu item's id given the restaurantID and item name
 * @param restaurantId
 * @param itemName
 * @return -1 if failed, otherwise return item ID.
 */
int Database::GetItemId(int restaurantId, QString itemName)
{
    QSqlQuery query;
    query.prepare("SELECT itemId from items where id = :restaurantId and name = :itemName");
    query.bindValue(":restaurantId", restaurantId);
    query.bindValue(":itemName", itemName);
    if(query.exec()){
        if(query.next()){
            return query.value("itemId").toInt();
        }
        else
        {
            qDebug() << "No menu item like that exists.";
        }
    }
    else
    {
        qDebug() << lastError().text();
        return -1;
    }
}

/**
 * @brief Database::PurchaseItem Add an item to the cart.
 * @param itemId The ID of the item to add.
 * @param quantity The quantity of items to purchase.
 * @return true if successfully added.
 */
bool Database::PurchaseItem(int itemId, int quantity)
{
    QSqlQuery query;

    query.prepare("INSERT INTO cart (id, quantity) "
                  "VALUES (:id, :quantity)");

    query.bindValue(":id", itemId);
    query.bindValue(":quantity", quantity);

    return query.exec();
}

/**
 * @brief Database::GetRestaurantDistances Retrieve the restaurant distances
 * @param restaurantName
 * @return int list
 */

QVector<double> Database::GetRestaurantDistances(QString name)
{
    QVector<double> 	distanceList;
    QSqlQuery 		query;
    int 		restaurantId;
    double 		distance;

    restaurantId = GetRestaurantId(name);

    query.prepare("SELECT `distance` FROM distances WHERE distances.from = :id");

    query.bindValue(":id", restaurantId);

    if(query.exec()){
        while(query.next())
        {
            distance = query.value("distance").toDouble();
            distanceList.append(distance);
        }
    }
    else
    {
        qDebug() << "Failed!";
        qDebug() << lastError().text();
    }
    return distanceList;
}


QVector<double> Database::GetRestaurantDistances(int restaurantId)
{
    QVector<double> 	distanceList;
    QSqlQuery 		query;
    double  	        distance;

    query.prepare("SELECT `distance` FROM distances WHERE distances.from = :id");

    query.bindValue(":id", restaurantId);

    if(query.exec()){
        while(query.next())
        {
            distance = query.value("distance").toDouble();
            distanceList.append(distance);
        }
    }
    else
    {
        qDebug() << "Failed!";
        qDebug() << lastError().text();
    }
    return distanceList;
}

QVector<int> Database::GetAllRestaurantIds() const
{
    QVector<int> 	restaurantIds;
    QSqlQuery 		query;
    int 		id;

    query.prepare("SELECT `id` FROM restaurants");

    if(query.exec()){
        while(query.next())
        {
            id = query.value("id").toInt();
            restaurantIds.append(id);
        }
    }
    else
    {
        qDebug() << "Failed!";
        qDebug() << lastError().text();
    }
    return restaurantIds;
}
