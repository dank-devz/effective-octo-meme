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
