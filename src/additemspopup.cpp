#include "additemspopup.h"
#include "ui_additemspopup.h"

AddItemsPopup::AddItemsPopup(QWidget *parent, int restID) :
    QDialog(parent),
    ui(new Ui::AddItemsPopup)
{
    ui->setupUi(this);
    _restID = restID;
}

AddItemsPopup::~AddItemsPopup()
{
    delete ui;
}

void AddItemsPopup::on_AddItemsPopup_buttonBox_accepted()
{
    if(!ui->AddItemsPopup_itemName_lineEdit->text().isEmpty())
    {
        QString itemName = ui->AddItemsPopup_itemName_lineEdit->text();
        double itemPrice = ui->AddItemsPopup_itemPrice_doubleSpinBox->value();
        emit MenuItemAdd(_restID, itemName, itemPrice);
        close();
    }

}

void AddItemsPopup::on_AddItemsPopup_buttonBox_rejected()
{
    close();
}
