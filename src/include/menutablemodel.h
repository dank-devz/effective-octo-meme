#ifndef MENUTABLEMODEL_H
#define MENUTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>
#include <QString>
#include "database.h"

/**
 * @brief The MenuTableModel class is a wrapper for QSqlTableModel
 * and displays the menu of a particular restaurant.
 */
class MenuTableModel : public QSqlTableModel
{
    Q_OBJECT
public:

    /// Fields in menu_view
    enum Fields
    {
        ID,
        ITEM,
        PRICE,
        ITEMID
    };

    /// Constructor
    MenuTableModel(QObject *parent, Database *db, int id);

    /// Initialize Model Settings
    void Initialize(int id);
};

#endif // MENUTABLEMODEL_H
