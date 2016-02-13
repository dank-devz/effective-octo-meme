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
    Database();

    ///Destructor
    ~Database();

private:
};

#endif // DATABASE_H
