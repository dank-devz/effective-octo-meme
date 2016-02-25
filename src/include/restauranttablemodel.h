#ifndef RESTAURANTTABLEMODEL_H
#define RESTAURANTTABLEMODEL_H
#include<QSqlTableModel>
#include <QObject>
#include "database.h"

class RestaurantTableModel : public QSqlTableModel
{
    Q_OBJECT
public:

    ///Fields in restaurants_view
    enum Fields
    {
        ID,
        NAME,
        DISTANCE
    };

    RestaurantTableModel(QObject *parent, Database *db);

    ///Initialize model settings
    void Initialize();
};

#endif // RESTAURANTTABLEMODEL_H
