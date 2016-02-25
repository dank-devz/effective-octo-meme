#ifndef MENUTABLEMODEL_H
#define MENUTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>
#include <QString>
#include "database.h"

class MenuTableModel : public QSqlTableModel
{
    Q_OBJECT
public:

    /// Fields in menu_view
    enum Fields
    {
        ID,
        ITEM,
        PRICE
    };

    /// Constructor
    MenuTableModel(QObject *parent, Database *db, int id);

    /// Initialize Model Settings
    void Initialize(int id);
};

#endif // MENUTABLEMODEL_H
