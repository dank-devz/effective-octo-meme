#ifndef CARTTABLEMODEL_H
#define CARTTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>
#include <QString>
#include "database.h"

/**
 * @brief The CartTableModel class is a wrapper for QSqlTableModel class
 * and displays the current cart database.
 */
class CartTableModel : public QSqlTableModel
{
    Q_OBJECT
public:

    /// Fields in menu_view
    enum Fields
    {
        QUANTITY,
        ID,
        NAME,
        PRICE
    };

    /// Constructor
    CartTableModel(QObject *parent, Database *db);

    /// Initialize Model Settings
    void Initialize();
};
#endif // CARTTABLEMODEL_H
