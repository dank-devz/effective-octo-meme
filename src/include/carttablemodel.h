#ifndef CARTTABLEMODEL_H
#define CARTTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>
#include <QString>
#include "database.h"

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
