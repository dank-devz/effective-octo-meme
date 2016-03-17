#ifndef RESTAURANTTABLEMODEL_H
#define RESTAURANTTABLEMODEL_H
#include<QSqlTableModel>
#include <QObject>
#include "database.h"

/**
 * @brief The RestaurantTableModel class is a wrapper for QSqlTableModel
 * and displays the restaurants_view table.
 */
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
