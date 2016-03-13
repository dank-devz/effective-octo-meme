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
    ui->primary_pushButton_next->setEnabled(false);
    ui->primary_label_error->hide();
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

void addRestaurant::on_primary_lineEdit_name_textChanged(const QString &arg1)
{
    ui->primary_pushButton_next->setEnabled(true);
}

void addRestaurant::on_primary_pushButton_cancel_clicked()
{
    QWidget::close();
}

// extracts the name from the form if the form is not empty
// note: if the form is empty the user cannot proceed
void addRestaurant::on_primary_pushButton_next_clicked()
{
    if(ui->primary_lineEdit_name->text().isEmpty())
        // displays an error for the user
        ui->primary_label_error->show();
    else
        // increments the index of the stacked widget
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

// extracts the name from the form if the form is not empty
// note: if the form is empty the user cannot proceed
void addRestaurant::on_primary_lineEdit_name_returnPressed()
{
    if(ui->primary_lineEdit_name->text().isEmpty())
        // displays an error for the user
        ui->primary_label_error->show();
    else
        // increments the indexf of the stacked widget
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);

}
