#include "../include/carttablemodel.h"

CartTableModel::CartTableModel(QObject *parent, Database *db)
{
    Initialize();
}

void CartTableModel::Initialize()
{
    this->setTable("cart_view");
    this->setHeaderData(NAME, Qt::Horizontal, tr("Item Name"),QSqlTableModel::OnManualSubmit);
    this->setHeaderData(PRICE, Qt::Horizontal, tr("Item Price"),QSqlTableModel::OnManualSubmit);
    this->setHeaderData(QUANTITY, Qt::Horizontal, tr("Quantity"),QSqlTableModel::OnManualSubmit);
    this->select();
}
