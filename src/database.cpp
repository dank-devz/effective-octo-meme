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
 * (╯°□°）╯︵ ┻━┻)
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
   //create query object and associate it with this database.
   QSqlQuery *query = new QSqlQuery(this);

   //prepare a SQL query with named binding
   query->prepare("INSERT INTO items (id, name, price) "
                  "VALUES (:id. :name, :price);");

   //bind values
   query->bindValue("id", restaurantId);
   query->bindValue(":name", itemName);
   query->bindValue(":price", price);

   return query->exec();
}
