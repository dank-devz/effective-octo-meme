#include "../include/carttablemodel.h"

CartTableModel::CartTableModel(QObject *parent, Database *db) : QSqlTableModel(parent, *db)
{
    Initialize();
}

void CartTableModel::Initialize()
{
    this->setTable("cart_view");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->setHeaderData(NAME, Qt::Horizontal, tr("Item Name"), 0);
    this->setHeaderData(PRICE, Qt::Horizontal, tr("Item Price"), 0);
    this->setHeaderData(QUANTITY, Qt::Horizontal, tr("Quantity"), 0);
    this->select();
}
