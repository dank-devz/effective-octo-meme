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
