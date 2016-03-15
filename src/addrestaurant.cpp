#include "addrestaurant.h"
#include "ui_addrestaurant.h"

addRestaurant::addRestaurant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRestaurant)
{
    ui->setupUi(this);
}

// constructor
addRestaurant::addRestaurant(QWidget *parent, Database *db) :
    QDialog(parent),
    ui(new Ui::addRestaurant)
{
    ui->setupUi(this);

    // sets the database pointer
    db_ = db;

    // initializations
    QWidget::setWindowTitle("Add Restaurant");
    ui->stackedWidget->setCurrentIndex(PAGE_PRIMARY);
    ui->primary_pushButton_next->setEnabled(false);
    otherLocations_ = db->GetAllRestaurantIds();
    otherLocationsCopy_ = otherLocations_;

    // hides all of the error message labels
    ui->primary_label_errorMessage->hide();
    ui->addItems_label_added->hide();
    ui->addItems_label_errorMessage->hide();
}

addRestaurant::addRestaurant(QWidget *parent, int restaurantId, Database *db) :
    QDialog(parent),
    ui(new Ui::addRestaurant)
{
    ui->setupUi(this);

    // sets the database pointer and the restaurant to have an item added
    db_ = db;
    restaurantId_ = restaurantId;
}


addRestaurant::~addRestaurant()
{
    delete ui;
}

// unlocks the next button
void addRestaurant::on_primary_lineEdit_name_textChanged(const QString &arg1)
{
    ui->primary_pushButton_next->setEnabled(true);
}

// closes the window
void addRestaurant::on_primary_pushButton_cancel_clicked()
{
    QWidget::close();
}

// extracts the name from the form if the form is not empty
// note: if the form is empty the user cannot proceed
void addRestaurant::on_primary_pushButton_next_clicked()
{
    if(ui->primary_lineEdit_name->text().isEmpty())
    {
        // displays an error for the user
        ui->primary_label_errorMessage->show();
    }
    else
    {
        // increments the indexf of the stacked widget
        ui->stackedWidget->setCurrentIndex(PAGE_ADD_ITEMS);
        restaurantName_ = ui->primary_lineEdit_name->text();
    }
}

// extracts the name from the form if the form is not empty
// note: if the form is empty the user cannot proceed
void addRestaurant::on_primary_lineEdit_name_returnPressed()
{
    if(ui->primary_lineEdit_name->text().isEmpty())
    {
        // displays an error for the user
        ui->primary_label_errorMessage->show();
    }
    else
    {
        // increments the indexf of the stacked widget
        ui->stackedWidget->setCurrentIndex(PAGE_ADD_ITEMS);
        restaurantName_ = ui->primary_lineEdit_name->text();
    }
}

// closes the window
void addRestaurant::on_addItems_pushButton_cancel_clicked()
{
    QWidget::close();
}

// takes the user to the distances page
void addRestaurant::on_addItems_pushButton_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(PAGE_ADD_DISTANCES);
    ui->addDistances_label_location->setText(db_->GetRestaurantName(otherLocationsCopy_.at(0)));
}

//
void addRestaurant::on_addItems_pushButton_add_clicked()
{
    if(ui->addItems_lineEdit_name->text().isEmpty())
    {
        ui->addItems_label_errorMessage->show();
    }
    else
    {
        menuItemNames_.push_back(ui->addItems_lineEdit_name->text());
        menuItemPrices_.push_back(ui->addItems_doubleSpinBox_price->value());
        ui->addItems_label_added->setText("Added " + ui->addItems_lineEdit_name->text());
        ui->addItems_label_errorMessage->hide();
        ui->addItems_label_added->show();
    }
}

// closes the window
void addRestaurant::on_addDistances_pushButton_cancel_clicked()
{
    QWidget::close();
}

// adds the
void addRestaurant::on_addDistances_pushButton_next_clicked()
{
    if(otherLocationsCopy_.size() == 1)
    {
        distances_.push_back(ui->addDistances_doubleSpinBox_distance->value());
        otherLocationsCopy_.pop_front();
        // take the data and store it into the db
        db_->AddNewRestaurant(restaurantName_, menuItemNames_, menuItemPrices_, otherLocations_, distances_);

        // closes the window
        QWidget::close();
    }
    else
    {
        distances_.push_back(ui->addDistances_doubleSpinBox_distance->value());
        otherLocationsCopy_.pop_front();
        /* Needs to be replaced with the name */
        ui->addDistances_label_location->setText(db_->GetRestaurantName(otherLocationsCopy_.at(0)));
        /* * */

        // changes the next text to signify that the admin only has on entry left
        if(otherLocationsCopy_.size() == 1)
            ui->addDistances_pushButton_next->setText("Finish");
    }
}
