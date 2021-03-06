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
 * @brief Database::AddRestaurant
 * Add a restaurant to the Database.
 * @param restaurantName
 * @return true if successful
 */
bool Database::AddRestaurant(QString restaurantName)
{
    QSqlQuery query;

    query.prepare("INSERT INTO restaurants (name)"
                  "VALUES (:name)");
    query.bindValue(":name", restaurantName);

    return query.exec();
}

/**
 * @brief Database::RemoveRestaurant
 * Remove a restaurant from the Database.
 * @param restaurantId
 * @return
 */
bool Database::RemoveRestaurant(int restaurantId)
{
    QSqlQuery query;

    query.prepare("DELETE FROM restaurants WHERE id = :id");
    query.bindValue(":id", restaurantId);

    return query.exec();
}

/**
 * @brief Database::RemoveRestaurant
 * @param restaurantName
 * @return
 */
bool Database::RemoveRestaurant(QString restaurantName)
{
    QSqlQuery query;

    query.prepare("DELETE FROM restaurants WHERE name = :name");
    query.bindValue(":name", restaurantName);

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

QString Database::GetRestaurantName(int id)
{
    QSqlQuery query;
    query.prepare("select name from restaurants where id = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        if(query.next())
        {
            return query.value("name").toString();
        }
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
    return -1;
}

/**
 * @brief Database::GetCartTotal Retrieve the total cost of the items in the cart.
 * @return Sum of the prices of items in the cart.
 */
double Database::GetCartTotal()
{
    QSqlQuery query;
    double totalCost = 0;
    query.exec("SELECT items.price, cart.quantity from cart, items where cart.id = items.itemId");
    while(query.next())
    {
        totalCost += (query.value("price").toDouble() * query.value("quantity").toInt());
    }
    return totalCost;
}

bool Database::AuthenticateAdmin(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT * from users where username=:username and password=:password and admin=1");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    return query.next();
}

/**
 * @brief Database::PurchaseItem Add an item to the cart.
 * @param itemId The ID of the item to add.
 * @param quantity The quantity of items to purchase.
 * @return true if successfully added.
 */
bool Database::PurchaseItem(int itemId, int quantity, QString name, double price)
{
    QSqlQuery query;

    query.prepare("INSERT INTO cart (id, quantity, name, price) "
                  "VALUES (:id, :quantity, :name, :price)");

    query.bindValue(":id", itemId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":name", name);
    query.bindValue(":price", price);

    return query.exec();
}

bool Database::UpdateQuantity(int quantity, int itemId)
{
    QSqlQuery query;
    query.prepare("UPDATE cart set cart.quantity = (cart.quantity + :quantity) where cart.id = :itemId");
    query.bindValue(":quantity", quantity);
    query.bindValue(":itemId", itemId);
    return query.exec();
}

bool Database::ClearCart()
{
    QSqlQuery query;
    return query.exec("delete from cart");
}

/**
 * @brief Database::AddNewRestaurant
 * Add a new restaurant and all related info.
 * @param restaurantName The name of the restaurant
 * @param menuItemNames THe names of the menu items
 * @param menuItemPrices The prices of the corresponding menu items
 * @param otherRestaurantIds The other restaurants ids
 * @param distances The distances
 * @return true if successful
 */
bool Database::AddNewRestaurant(QString restaurantName, QVector<QString> menuItemNames,
                                QVector<double> menuItemPrices, QVector<int> otherRestaurantIds,
                                QVector<double> distances)
{
    QSqlQuery query;
    bool success = false;

    if(AddRestaurant(restaurantName))
    {
        int id = GetRestaurantId(restaurantName);
        QVector<QString>::iterator str_it = menuItemNames.begin();
        QVector<double>::iterator double_it = menuItemPrices.begin();
        while(str_it != menuItemNames.end() && double_it != menuItemPrices.end()){
            success = AddMenuItem(id, *str_it, *double_it);
            str_it++;
            double_it++;
        }
        QVector<int>::iterator int_it = otherRestaurantIds.begin();
        double_it = distances.begin();
        while(int_it != otherRestaurantIds.end() && double_it != distances.end()){
            success = AddDistance(id, *int_it, *double_it);
            success = AddDistance(*int_it, id, *double_it);
            int_it++;
            double_it++;
        }
        AddDistance(id, id, 0);
    }
    return success;
}

bool Database::AddDistance(int from, int to, double distance)
{
    QSqlQuery query;

    query.prepare("INSERT INTO distances (`from`, `to`, `distance`)"
                  "VALUES (:from, :to, :distance)");
    query.bindValue(":from", from);
    query.bindValue(":to", to);
    query.bindValue(":distance", distance);
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

/**
 * @brief Database::GetRestaurantDistances
 * Get a list of all the distances given a restaurant ID
 * @param restaurantId
 * @return QVector of distances
 */
QVector<double> Database::GetRestaurantDistances(int restaurantId)
{
    QVector<double> 	distanceList(11);
    QSqlQuery 		    query;
    int                 id;
    double  	        distance;

    query.prepare("SELECT distances.`distance`, distances.`to` FROM distances WHERE distances.`from` = :id order by distances.`to` asc");
    query.bindValue(":id", restaurantId);

    if(query.exec()){
        while(query.next())
        {
            distance = query.value("distance").toDouble();
            id = query.value("to").toInt();

            // expan vector if need be (id+1 since size starts at 0)
            if(distanceList.size() < id+1){
                distanceList.resize(id+1);
            }
            // insert distance at proper index
            distanceList.replace(id, distance);
        }
    }
    else
    {
        qDebug() << "Failed!";
        qDebug() << lastError().text();
    }
    return distanceList;
}

/**
 * @brief Database::GetAllRestaurantIds
 * Retrieve a list of all restaurant IDs in the Database.
 * @return QVector of restaurantIDs
 */
QVector<int> Database::GetAllRestaurantIds() const
{
    QVector<int> 	restaurantIds;
    QSqlQuery 		query;
    int 		    id;

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

/**
 * @brief Database::GetAllRestaurantNames
 * Retrieve a list of all Restaurant names.
 * @return A QVector of all restaurant names.
 */
QVector<QString> Database::GetAllRestaurantNames() const
{
    QVector<QString> restaurantNames;
    QSqlQuery query;

    query.prepare("SELECT name from restaurants");
    if(query.exec()){
        while(query.next()){
            restaurantNames.append(query.value("name").toString());
        }
    }
    else
    {
        qDebug() << "Dun goofed.";
        qDebug() << lastError().text();
    }
    return restaurantNames;
}

/**
 * @brief Database::GetRestaurantMenuItemNames
 * Get a list of all the menu item names given a restaurant ID.
 * @param restaurantId
 * @return A QList of all menu item names for a particular restaurant.
 */
QList<QString> Database::GetRestaurantMenuItemNames(int restaurantId)
{
    QList <QString> restaurantItemNames;
    QSqlQuery 		query;
    QString			itemName;

    query.prepare("SELECT `name` FROM `items` WHERE `items`.`id` = :id");
    query.bindValue(":id", restaurantId);

    if(query.exec()){
        while(query.next())
        {
            itemName = query.value("name").toString();
            restaurantItemNames.append(itemName);
        }
    }
    else
    {
        qDebug() << "Failed!";
        qDebug() << lastError().text();
    }
    return restaurantItemNames;
}

/**
 * @brief Database::GetItemPrice
 * Get the price for a particular item given its ID.
 * @param itemId
 * @return A double representing the price of the item.
 */
double Database::GetItemPrice(int itemId)
{
    QSqlQuery 		query;
    double	itemPrice = 0;

    query.prepare("SELECT `price` FROM `items` WHERE `items`.`itemid` = :id");
    query.bindValue(":id", itemId);

    if(query.exec()){
        if(query.next())
        {
            itemPrice = query.value("price").toDouble();
        }
    }
    else
    {
        qDebug() << "failed!";
        qDebug() << lastError().text();
    }
    return itemPrice;
}

/**
 * @brief Database::GetItemPrice
 * Get the item price given its name. (This might not work if more than
 * one item have the same name).
 * @param itemName
 * @return A double representing the price of the item.
 */
double Database::GetItemPrice(QString itemName)
{
    QSqlQuery 		query;
    double	itemPrice = 0;

    query.prepare("select `price` from `items` where `items`.`name` = :name");
    query.bindValue(":name", itemName);

    if(query.exec()){
        if(query.next())
        {
            itemPrice = query.value("price").toDouble();
        }
    }
    else
    {
        qDebug() << "failed!";
        qDebug() << lastError().text();
    }
    return itemPrice;
}
