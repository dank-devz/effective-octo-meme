#include "include/database.h"

/*!
 * \brief Database::Database
 * \param path path to sql database file
 */
Database::Database() : QSqlDatabase(addDatabase("QMYSQL"))
{
  setDatabaseName("fast_food_restaurants");
  setHostName("cs1d-fast-food-fantasy.cjv0rqkpv8ys.us-west-1.rds.amazonaws.com");
  setUserName("dankdevz");
  setPassword("cs1d-fast-food-fantasy");
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

   //prepare a SQL query with positional binding
   //note: I tried this with named binding and it did not work. (╯°□°）╯︵ ┻━┻)
   query.prepare("INSERT INTO items (id, name, price) "
                  "VALUES (?, ?, ?)");

   //bind values respectively
   query.addBindValue(restaurantId);
   query.addBindValue(itemName);
   query.addBindValue(price);

   return query.exec();
}
