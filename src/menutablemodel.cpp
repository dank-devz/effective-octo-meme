#include "include\menutablemodel.h"

MenuTableModel::MenuTableModel(QObject *parent, Database *db, int id) : QSqlTableModel(parent, *db)
{
    Initialize(id);
}

/*!
 * \brief MenuTableModel::Initialize
 * Set the table to display and all column labels.
 */
void MenuTableModel::Initialize(int id)
{
    QString filter = QString("id='%1'").arg(id);
    this->setTable("items");
    this->setHeaderData(ID, Qt::Horizontal, tr("Restaurant ID"),QSqlTableModel::OnManualSubmit);
    this->setHeaderData(ITEM, Qt::Horizontal, tr("Item Name"),QSqlTableModel::OnManualSubmit);
    this->setHeaderData(PRICE, Qt::Horizontal, tr("Price"),QSqlTableModel::OnManualSubmit);
    this->setFilter(filter);
    this->select();
}
