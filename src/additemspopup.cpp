#include "additemspopup.h"
#include "ui_additemspopup.h"

/**
 * @brief AddItemsPopup::AddItemsPopup
 * Constructor
 * @param parent
 * @param restID ID of the restaurant to add items to
 */
AddItemsPopup::AddItemsPopup(QWidget *parent, int restID) :
    QDialog(parent),
    ui(new Ui::AddItemsPopup)
{
    ui->setupUi(this);
    _restID = restID;
}

/**
 * @brief AddItemsPopup::~AddItemsPopup
 * Destructor
 */
AddItemsPopup::~AddItemsPopup()
{
    delete ui;
}

/**
 * @brief AddItemsPopup::on_AddItemsPopup_buttonBox_accepted
 * Emits a signal to add an item if successful.
 */
void AddItemsPopup::on_AddItemsPopup_buttonBox_accepted()
{
    if(!ui->AddItemsPopup_itemName_lineEdit->text().isEmpty())
    {
        QString itemName = ui->AddItemsPopup_itemName_lineEdit->text();
        double itemPrice = ui->AddItemsPopup_itemPrice_doubleSpinBox->value();
        emit MenuItemAdd(_restID, itemName, itemPrice);
        close();
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please enter an item name.");
        p->exec();
    }
}

void AddItemsPopup::on_AddItemsPopup_buttonBox_rejected()
{
    close();
}
