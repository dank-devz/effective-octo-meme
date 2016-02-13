#include "../include/mainwindow.h"
#include <QApplication>

#include <QCoreApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("fast_food_restaurants");
    db.setHostName("cs1d-fast-food-fantasy.cjv0rqkpv8ys.us-west-1.rds.amazonaws.com");
//    db.setDatabaseName("cs1d-fast-food-fantasy");
    QString username = "dankdevz";
    QString password = "cs1d-fast-food-fantasy";
    db.setUserName(username);
    db.setPassword(password);
    if(!db.open()){
        qDebug() << "Database error occurred";
        qDebug() << db.lastError();
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()){
        qDebug() << "Not connected!";
        return 1;
    }
    else {
        qDebug() << "Connected";
        QSqlQuery query;
        qDebug() << query.exec("SHOW TABLES;");

    }

    MainWindow w;
    w.show();

    return a.exec();
}
