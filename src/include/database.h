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
    bool AddMenuItem(int restaurantId, QString itemName, double price);

private:
};

#endif // DATABASE_H
