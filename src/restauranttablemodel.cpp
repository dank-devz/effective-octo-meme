#include "include/restauranttablemodel.h"

RestaurantTableModel::RestaurantTableModel(QObject *parent, Database *db) : QSqlTableModel(parent, *db)
{
    Initialize();
}

/*!
 * \brief RestaurantTableModel::Initialize
 * Set the table to display and all column labels.
 */
void RestaurantTableModel::Initialize()
{
    this->setTable("restaurants_view");
    this->setHeaderData(ID, Qt::Horizontal, tr("Restaurant ID"),QSqlTableModel::OnManualSubmit);
    this->setHeaderData(NAME, Qt::Horizontal, tr("Restaurant Name"),QSqlTableModel::OnManualSubmit);
    this->setHeaderData(DISTANCE, Qt::Horizontal, tr("Distance from Saddleback"),QSqlTableModel::OnManualSubmit);
    this->setFilter("");
    this->select();
}
