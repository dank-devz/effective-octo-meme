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
    restaurantId_ = -1;

    // hides all of the error message labels
    ui->primary_label_errorMessage->hide();
    ui->addItems_label_errorMessage->hide();
    ui->addItems_label_added->hide();
}

addRestaurant::addRestaurant(QWidget *parent, int restaurantId, Database *db) :
    QDialog(parent),
    ui(new Ui::addRestaurant)
{
    ui->setupUi(this);

    // sets the database pointer and the restaurant to have an item added
    db_ = db;
    restaurantId_ = restaurantId;

    // hides all of the error message labels
    ui->addItems_label_errorMessage->hide();
    ui->addItems_label_added->hide();
    ui->addItems_pushButton_cancel->hide();

    // sets the titles
    QWidget::setWindowTitle("Add Items");
    ui->addItems_label_title->setText("Adding items for " + db_->GetRestaurantName(restaurantId_));
    ui->addItems_pushButton_next->setText("Done");
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
    // case: adding menu items -> closes the window
    if(restaurantId_ > 0)
    {
        QWidget::close();
    }
    // case: new restaurant -> goes to get locations page
    else
    {
        ui->stackedWidget->setCurrentIndex(PAGE_ADD_DISTANCES);
        ui->addDistances_label_location->setText(db_->GetRestaurantName(otherLocationsCopy_.at(0)));
    }
}

// adds the current value to the vector if it is a new restaurant or
// sends it to the db if it is an existing one
void addRestaurant::on_addItems_pushButton_add_clicked()
{
    // case: no name value
    if(ui->addItems_lineEdit_name->text().isEmpty())
    {
        ui->addItems_label_errorMessage->show();
    }
    // case: windows is set to add items for a set restaurant
    // note: the restaurantId is set to -1 for the case of a new restaurant so this
    // section will be skipped
    else if(restaurantId_ > 0)
    {
        db_->AddMenuItem(restaurantId_, ui->addItems_lineEdit_name->text(), ui->addItems_doubleSpinBox_price->value());
        ui->addItems_label_added->setText("Added " + ui->addItems_lineEdit_name->text());
        ui->addItems_label_added->show();
        ui->addItems_label_errorMessage->hide();
    }
    // case: adding a new restaurant's menu
    else
    {
        menuItemNames_.push_back(ui->addItems_lineEdit_name->text());
        menuItemPrices_.push_back(ui->addItems_doubleSpinBox_price->value());
        ui->addItems_label_added->setText("Added " + ui->addItems_lineEdit_name->text());
        ui->addItems_label_added->show();
        ui->addItems_label_errorMessage->hide();
    }
}

// closes the window
void addRestaurant::on_addDistances_pushButton_cancel_clicked()
{
    QWidget::close();
}

// adds the locations to the location vector and sends the data into the db after
// the final form is filled
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
