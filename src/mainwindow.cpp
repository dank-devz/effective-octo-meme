#include "include/mainwindow.h"
#include "include/adminlogin.h"
#include "ui_mainwindow.h"
#include "addrestaurant.h"
#include <iostream>
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // sets the default page to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);

    // instantiate the database and the model
    db = new Database("fast_food_restaurants", "cs1d-fast-food-fantasy.cjv0rqkpv8ys.us-west-1.rds.amazonaws.com",
                      "dankdevz", "cs1d-fast-food-fantasy");

    initViewAllRestaurantsTable();
    initializeAdminFeatures();

    this->the_trip_ = new Trip(db);
    this->tripStopsModel = new QStandardItemModel(this);

    cartTotal = 0;
}

MainWindow::~MainWindow()
{
    db->ClearCart();
    delete ui;
}

/**
 * @brief MainWindow::toggleAdminFeatures
 * Make special admin buttons appear, make tables editable.
 * @param isAdmin
 */
void MainWindow::toggleAdminFeatures(bool isAdmin)
{
    if(isAdmin)
    {

        QMessageBox *success = new QMessageBox(this);
        success->setText("You are the Dankest Admin");
        success->exec();
        ui->tableView->setEditTriggers(QTableView::DoubleClicked);
        ui->viewAllRestaurants_tableView->setEditTriggers(QTableView::DoubleClicked);
        QFile file(":/qss/darkorange.qss");
           if(file.open(QIODevice::ReadOnly | QIODevice::Text))
           {
               setStyleSheet(file.readAll());
               file.close();
           }
    }
    else
    {
        ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
        ui->viewAllRestaurants_tableView->setEditTriggers(QTableView::NoEditTriggers);
        QFile file(":/qss/darkgreen.qss");
           if(file.open(QIODevice::ReadOnly | QIODevice::Text))
           {
               setStyleSheet(file.readAll());
               file.close();
           }
    }
    ui->actionAdd_Remove_Restaurants->setEnabled(isAdmin);
    ui->actionAdd_Remove_Restaurants->setVisible(isAdmin);

    ui->admin_viewAllRestaurants_addRestaurant_pushButton->setEnabled(isAdmin);
    ui->admin_viewAllRestaurants_addRestaurant_pushButton->setVisible(isAdmin);

    ui->admin_viewAllRestaurants_removeRestaurant_pushButton->setEnabled(isAdmin);
    ui->admin_viewAllRestaurants_removeRestaurant_pushButton->setVisible(isAdmin);

    ui->admin_viewDetails_addMenuItem_pushButton->setEnabled(isAdmin);
    ui->admin_viewDetails_addMenuItem_pushButton->setVisible(isAdmin);

    ui->admin_viewDetails_removeMenuItem_pushButton->setEnabled(isAdmin);
    ui->admin_viewDetails_removeMenuItem_pushButton->setVisible(isAdmin);

    ui->admin_submitChanges_menu_pushButton->setEnabled(isAdmin);
    ui->admin_submitChanges_menu_pushButton->setVisible(isAdmin);

    ui->admin_submitChanges_restaurant_pushButton->setEnabled(isAdmin);
    ui->admin_submitChanges_restaurant_pushButton->setVisible(isAdmin);
}

void MainWindow::AddMenuItem(int restID, QString name, double price)
{
    db->AddMenuItem(restID, name, price);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_home_pushButton_viewAllRestaurants_clicked()
{
    // takes the user to the viewAllRestaurants page (index - 1)
    ui->stackedWidget->setCurrentIndex(PAGE_VIEW_ALL_RESTAURANTS);
    ui->viewAllRestaurants_tableView->hideColumn(0);
}

void MainWindow::on_home_pushButton_planRegularFoodRun_clicked()
{
    // takes the user to the planRegularFoodRun page (index - 2)
    ui->stackedWidget->setCurrentIndex(PAGE_PLAN_REGULAR_TRIP);

    // fills the combo boxes with the most recent values from the db
    QList<QString> restaurants = db->GetRestaurants();
    ui->planRegularTrip_comboBox_numberOfStops->clear();
    ui->planRegularTrip_comboBox_startingLocation->clear();
    for(int i = 0; i < restaurants.size(); i ++)
    {
        ui->planRegularTrip_comboBox_numberOfStops->addItem(QString::number(i+1));
        ui->planRegularTrip_comboBox_startingLocation->addItem(restaurants.at(i));
    }

    // resets the tripStops vector and model
    tripStops.clear();
    tripStopsModel->clear();

    // resets the trip class' calculator
    the_trip_->resetTripCalc();
}

void MainWindow::on_home_pushButton_planCustomFoodRun_clicked()
{
    initializeCustomTripPage();
    // takes the user to the planCustomFoodRun page (index - 3)
    ui->stackedWidget->setCurrentIndex(PAGE_PLAN_CUSTOM_TRIP);
}

void MainWindow::on_viewAllRestaurants_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);
}

void MainWindow::on_viewAllRestaurants_pushButton_viewDetails_clicked()
{
    // Get the information for the currently selected item
    int currentRow         = ui->viewAllRestaurants_tableView->currentIndex().row();
    if(currentRow > -1)
    {
        qDebug() << "currentRow: " << currentRow;
        QModelIndex nameIndex  = ui->viewAllRestaurants_tableView->model()->index(currentRow, 1);
        QModelIndex idIndex    = ui->viewAllRestaurants_tableView->model()->index(currentRow, 0);

        // Get the Restaurant name and location ID
        int locationID = ui->viewAllRestaurants_tableView->model()->data(idIndex).toInt();
        QString Title  = ui->viewAllRestaurants_tableView->model()->data(nameIndex).toString() + "'s Menu";
        qDebug() << "Showing Menu for Location " << locationID << ", " << Title;

        // Fill the view with the infos
        ui->label->setText(Title);
        initViewDetailsTable(locationID);

        // takes the user to the view details page
        ui->stackedWidget->setCurrentIndex(PAGE_VIEW_DETAILS);
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please select a row.");
        p->setStandardButtons(QMessageBox::Ok);
        p->exec();
    }
}

void MainWindow::on_planRegularTrip_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);
}


void MainWindow::on_planRegularTrip_pushButton_go_clicked()
{
    // takes the user to the view details page
    ui->stackedWidget->setCurrentIndex(PAGE_CART_ITEMS);

    qDebug() << db->GetRestaurantId(ui->planRegularTrip_comboBox_startingLocation->currentText()) << endl;
    qDebug() << ui->planRegularTrip_comboBox_numberOfStops->currentText().toInt() << endl;

    // generates the list of locations to be visited
    QVector<int> allLocations = db->GetAllRestaurantIds();
    tripStops = the_trip_->findRouteGreedy(allLocations, // vector of all of the locations
                                           db->GetRestaurantId(ui->planRegularTrip_comboBox_startingLocation->currentText()), // the starting location
                                           ui->planRegularTrip_comboBox_numberOfStops->currentText().toInt());// the total number of stops

    // Fill the view with the info
    ui->cartItems_label_restaurant_name->setText(db->GetRestaurantName(tripStops.at(0)) + "\'s Menu");
    initCartItemsTable(tripStops.at(0));
    ui->cartItems_tableView_items->hideColumn(MenuTableModel::ID);

    //
    if(tripStops.size() == 1){
        ui->cartItems_pushButton_next->setText("Finish");
    }
    else{
        ui->cartItems_pushButton_next->setText("Next");
    }

    // gets the model ready for the final diplsay page
    tripStopsModel->clear();
    for(int i = 0; i < tripStops.size(); i++)
    {
        tripStopsModel->insertRow(i, new QStandardItem(db->GetRestaurantName(tripStops.at(i))));
    }
}

void MainWindow::on_planCustomFoodRun_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);
}

void MainWindow::on_viewDetails_pushButton_back_clicked()
{
    // takes the user back to the viewAllRestaurants page (index - 1)
    ui->stackedWidget->setCurrentIndex(PAGE_VIEW_ALL_RESTAURANTS);
}

void MainWindow::initViewAllRestaurantsTable()
{
    restaurantModel = new RestaurantTableModel(this, db);
    ui->viewAllRestaurants_tableView->setModel(restaurantModel);
    ui->viewAllRestaurants_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->viewAllRestaurants_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->viewAllRestaurants_tableView->verticalHeader()->setVisible(false);
    ui->viewAllRestaurants_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->viewAllRestaurants_tableView->resizeColumnsToContents();
    ui->viewAllRestaurants_tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::initViewDetailsTable(int id)
{
    menuModel = new MenuTableModel(this, db, id);
    ui->tableView->setModel(menuModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->hideColumn(MenuTableModel::ITEMID);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->hideColumn(0);
    ui->viewAllRestaurants_tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::initCartItemsTable(int id)
{
    menuModel = new MenuTableModel(this, db, id);
    cartModel = new CartTableModel(this, db);

    //table on top
    ui->cartItems_tableView_items->setModel(menuModel);
    ui->cartItems_tableView_items->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartItems_tableView_items->hideColumn(MenuTableModel::ITEMID);
    ui->cartItems_tableView_items->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cartItems_tableView_items->verticalHeader()->setVisible(false);
    ui->cartItems_tableView_items->horizontalHeader()->setStretchLastSection(true);

    //table on bottom
    ui->cartItems_tableView_reciept->setModel(cartModel);
    ui->cartItems_tableView_reciept->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartItems_tableView_reciept->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cartItems_tableView_reciept->verticalHeader()->setVisible(false);
    ui->cartItems_tableView_reciept->hideColumn(CartTableModel::ID);
    ui->cartItems_tableView_reciept->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_cartItems_addSelected_clicked()
{

    // Get the information for the currently selected item
    int currentRow          = ui->cartItems_tableView_items->currentIndex().row();
    QModelIndex nameIndex   = ui->cartItems_tableView_items->model()->index(currentRow, 1);
    QModelIndex itemIdIndex = ui->cartItems_tableView_items->model()->index(currentRow, 3);
    QModelIndex priceIndex  = ui->cartItems_tableView_items->model()->index(currentRow, 2);

    // Get the Restaurant name and location ID
    int itemId = ui->cartItems_tableView_items->model()->data(itemIdIndex).toInt();
    QString itemName  = ui->cartItems_tableView_items->model()->data(nameIndex).toString();
    double itemPrice = ui->cartItems_tableView_items->model()->data(priceIndex).toDouble();
    int quantity = ui->cartItems_spinBox_quantity->value();

    if(currentRow > -1)
    {
        if(!db->PurchaseItem(itemId, quantity, itemName, itemPrice)){
            //add quantity to item instead of re-adding same item
            db->UpdateQuantity(quantity, itemId);
        }
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please select an item to add to the cart.");
        p->exec();
    }
    cartModel->select();
    cartTotal += (itemPrice * quantity);
    ui->cartItems_label_totalValue->setText("$ " + QString::number(cartTotal));
    ui->cartItems_spinBox_quantity->setValue(1);

    ui->cartItems_tableView_reciept->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cartItems_tableView_reciept->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartItems_tableView_reciept->resizeColumnsToContents();
}

void MainWindow::on_cartItems_pushButton_Back_clicked()
{
    // re-initializes the spin box quantity
    ui->cartItems_spinBox_quantity->setValue(1);
    // returns back to the planning page
    ui->stackedWidget->setCurrentIndex(PAGE_PLAN_REGULAR_TRIP);
}

void MainWindow::on_cartItems_removeSelected_clicked()
{

    if(cartModel->removeRow(ui->cartItems_tableView_reciept->currentIndex().row()))
    {
        int currentRow          = ui->cartItems_tableView_reciept->currentIndex().row();
        QModelIndex priceIndex  = ui->cartItems_tableView_reciept->model()->index(currentRow, 3);
        QModelIndex quantityIndex  = ui->cartItems_tableView_reciept->model()->index(currentRow, 0);
        double itemPrice = ui->cartItems_tableView_reciept->model()->data(priceIndex).toDouble();
        int quantity = ui->cartItems_tableView_reciept->model()->data(quantityIndex).toInt();
        cartTotal -= (itemPrice * quantity);
        qDebug() << "cart Total: " << cartTotal;

        cartModel->submitAll();
        ui->cartItems_label_totalValue->setText("$ " + QString::number(cartTotal));
        cartModel->select();
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please select an item to remove from the cart.");
        p->exec();
    }
}

void MainWindow::on_actionLogin_triggered()
{
    AdminLogin *adminPrompt;
    adminPrompt = new AdminLogin(this, db);
    QObject::connect(adminPrompt, SIGNAL(adminStatusChanged(bool)),
                     this, SLOT(toggleAdminFeatures(bool)));
    adminPrompt->setWindowModality(Qt::ApplicationModal);
    adminPrompt->show();

}

void MainWindow::on_actionLogout_triggered()
{
    emit adminStatusChanged(false);
}

void MainWindow::adminButtonsShow()
{
    ui->home_pushButton_planRegularFoodRun->setText("Edit Restaurant Menu Items");
}

void MainWindow::adminButtonsHide()
{
    ui->home_pushButton_planRegularFoodRun->setText("View Nearby Restaurants");
}

void MainWindow::on_cartItems_pushButton_next_clicked()
{
    if(tripStops.size() == 1)
    {
        ui->tripSummary_tableView_reciept->setModel(cartModel);
        ui->tripSummary_tableView_reciept->setEditTriggers(QTableView::NoEditTriggers);
        ui->tripSummary_tableView_reciept->hideColumn(CartTableModel::ID);
        ui->tripSummary_tableView_reciept->verticalHeader()->setVisible(false);
        ui->tripSummary_tableView_reciept->horizontalHeader()->setStretchLastSection(true);
        cartModel->select();
        ui->tripSummary_label_totalSpentValue->setText(QString::number(db->GetCartTotal()));
        ui->tripSummary_label_totalDistanceTraveledValue->setText(QString::number(the_trip_->getDistance()) + " miles!");
        ui->stackedWidget->setCurrentIndex(PAGE_TRIP_SUMMARY);

        // sets the stops table in the trip summary
        ui->tripSummary_listView_stops->setModel(tripStopsModel);
    }
    else
    {
        cartTotal = 0;
        ui->cartItems_label_totalValue->setText(QString::number(cartTotal));
        tripStops.pop_front();
        //refresh menu
        initCartItemsTable(tripStops.front());
        cartModel->select();

        ui->cartItems_label_restaurant_name->setText(db->GetRestaurantName(tripStops.at(0)));

        // changes the next text to signify that the admin only has on entry left
        if(tripStops.size() == 1)
            ui->cartItems_pushButton_next->setText("Finish");
    }
}

void MainWindow::on_admin_submitChanges_menu_pushButton_clicked()
{
    menuModel->submitAll();
    qDebug() << "Changes submitted to menu table.";
}

void MainWindow::on_admin_submitChanges_restaurant_pushButton_clicked()
{
    restaurantModel->submitAll();
    qDebug() << "Changes submitted to restaurant table.";
}

void MainWindow::initializeAdminFeatures()
{
    ui->actionAdd_Remove_Restaurants->setVisible(false);
    QObject::connect(this, SIGNAL(adminStatusChanged(bool)),
                     this, SLOT(toggleAdminFeatures(bool)));
    ui->admin_submitChanges_menu_pushButton->setVisible(false);
    ui->admin_submitChanges_restaurant_pushButton->setVisible(false);
    ui->admin_viewDetails_addMenuItem_pushButton->setVisible(false);
    ui->admin_viewDetails_removeMenuItem_pushButton->setVisible(false);
    ui->admin_viewAllRestaurants_addRestaurant_pushButton->setVisible(false);
    ui->admin_viewAllRestaurants_removeRestaurant_pushButton->setVisible(false);
    ui->viewAllRestaurants_tableView->setEditTriggers(0);
    ui->tableView->setEditTriggers(0);
}

void MainWindow::initializeCustomTripPage()
{
    // fills the combo box with the most recent restaurants from the db
    QList<QString> restaurants = db->GetRestaurants();
    ui->planCustomFoodRun_comboBox_locations->clear();
    for(int i = 0; i < restaurants.size(); i ++)
    {
        ui->planCustomFoodRun_comboBox_locations->addItem(restaurants.at(i));
    }

    // enables the add button
    ui->planCustomFoodRun_pushButton_add->setEnabled(true);

    // resets the tripStops vector and model
    tripStops.clear();
    tripStopsModel->clear();

    // resets the trip class' calculator
    the_trip_->resetTripCalc();
}

void MainWindow::on_admin_viewAllRestaurants_addRestaurant_pushButton_clicked()
{
    addRestaurant *p = new addRestaurant(this, db);
    p->exec();
    restaurantModel->select();
    the_trip_->refreshLocations(db);
}

void MainWindow::on_admin_viewAllRestaurants_removeRestaurant_pushButton_clicked()
{
    if(restaurantModel->removeRow(ui->viewAllRestaurants_tableView->currentIndex().row()))
    {
        int currentRow          = ui->viewAllRestaurants_tableView->currentIndex().row();
        QModelIndex nameIndex   = ui->viewAllRestaurants_tableView->model()->index(currentRow, 1);
        QString restaurantName  = ui->viewAllRestaurants_tableView->model()->data(nameIndex).toString();
        QMessageBox *p = new QMessageBox(this);
        p->setText(restaurantName + " will be removed.");
        p->setInformativeText("Are you sure?");
        p->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        p->setDefaultButton(QMessageBox::Cancel);
        int decision = p->exec();
        if(decision == QMessageBox::Ok)
        {
            db->RemoveRestaurant(restaurantName);
            qDebug() << restaurantModel->lastError();
            restaurantModel->select();
        }
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please select a row.");
        p->setStandardButtons(QMessageBox::Ok);
        p->exec();
    }
    // Refresh the trip data
    the_trip_->refreshLocations(db);
}


void MainWindow::on_admin_viewDetails_removeMenuItem_pushButton_clicked()
{
    if(menuModel->removeRow(ui->tableView->currentIndex().row()))
    {
        int currentRow          = ui->tableView->currentIndex().row();
        QModelIndex restaurantID_index  = ui->tableView->model()->index(currentRow, 0);
        QModelIndex nameIndex   = ui->tableView->model()->index(currentRow, 1);
        QString itemName  = ui->tableView->model()->data(nameIndex).toString();
        int restaurantID        = ui->tableView->model()->data(restaurantID_index).toInt();
        QMessageBox *p = new QMessageBox(this);
        p->setText(itemName + " will be removed.");
        p->setInformativeText("Are you sure?");
        p->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        p->setDefaultButton(QMessageBox::Cancel);
        int decision = p->exec();
        if(decision == QMessageBox::Ok)
        {
            db->RemoveMenuItem(restaurantID, itemName);
            qDebug() << db->lastError();
            menuModel->select();
        }
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please select a row.");
        p->setStandardButtons(QMessageBox::Ok);
        p->exec();
    }
}

void MainWindow::on_admin_viewDetails_addMenuItem_pushButton_clicked()
{
    QModelIndex restaurantID_index  = ui->tableView->model()->index(0, 0);
    int restaurantID        = ui->tableView->model()->data(restaurantID_index).toInt();
    AddItemsPopup *p = new AddItemsPopup(this, restaurantID);
    QObject::connect(p, SIGNAL(MenuItemAdd(int,QString,double)),
                     this, SLOT(AddMenuItem(int,QString,double)));
    p->exec();
    menuModel->select();
}

void MainWindow::on_planCustomFoodRun_pushButton_add_clicked()
{
    // adds the item to the tripStops list
    tripStops.push_back(db->GetRestaurantId(ui->planCustomFoodRun_comboBox_locations->currentText()));

    // adds the item to the tripStops list view
    tripStopsModel->insertRow(tripStopsModel->rowCount(), new QStandardItem(ui->planCustomFoodRun_comboBox_locations->currentText()));
    ui->planCustomFoodRun_listView_selected->setModel(tripStopsModel);

    // removes the current item from the combo box so it cannot be selected again
    ui->planCustomFoodRun_comboBox_locations->removeItem(ui->planCustomFoodRun_comboBox_locations->currentIndex());

    // disables the add button if there is no more restaurants to add
    if(ui->planCustomFoodRun_comboBox_locations->currentText() == "")
        ui->planCustomFoodRun_pushButton_add->setEnabled(false);
}

void MainWindow::on_planCustomFoodRun_pushButton_go_clicked()
{
    if(tripStops.size() != 0){
    tripStops = the_trip_->findRouteGreedy(tripStops);
    ui->stackedWidget->setCurrentIndex(PAGE_CART_ITEMS);
    ui->cartItems_label_restaurant_name->setText(db->GetRestaurantName(tripStops.at(0)));

    // Fill the view with the infos
    ui->cartItems_label_restaurant_name->setText(db->GetRestaurantName(tripStops.at(0)) + "\'s Menu");
    initCartItemsTable(tripStops.at(0));
    ui->cartItems_tableView_items->hideColumn(MenuTableModel::ID);

    //
    if(tripStops.size() == 1){
        ui->cartItems_pushButton_next->setText("Finish");
    }
    else{
        ui->cartItems_pushButton_next->setText("Next");
    }

    // gets the model ready for the final diplsay page
    tripStopsModel->clear();
    for(int i = 0; i < tripStops.size(); i++)
    {
        tripStopsModel->insertRow(i, new QStandardItem(db->GetRestaurantName(tripStops.at(i))));
    }
    }
    else
    {
        QMessageBox *p = new QMessageBox(this);
        p->setText("Please select some restaurants to visit.");
        p->setStandardButtons(QMessageBox::Ok);
        p->exec();
    }
}

//cartTotal = 0;
//QVector<int> restId;
//int numToVisit = ui->planRegularTrip_comboBox_numberOfStops->currentText().toInt();
//int startPosition ;

//startPosition = db->GetRestaurantId(ui->planRegularTrip_comboBox_startingLocation->currentText());

//qDebug() << "Number of stops selected" << numToVisit;
//for(int index = 0; index < numToVisit; index++)
//{
//    restId.push_back(index + 1);
//    qDebug() << "Getting the distances from restaurant id : " << index + 1;
//    qDebug() << db->GetRestaurantDistances(index+1);
//}

////    the_trip_->findRouteBrute(restId);
//qDebug () << "Selected starting position is : " << ui->planRegularTrip_comboBox_startingLocation->currentText();

//this->the_trip_->findRouteGreedy(restId,startPosition);

//restId.clear();

//QString distance = QString::number(the_trip_->getDistance());
//ui->tripSummary_label_totalDistanceTraveledValue->setText(distance);
//numToVisit = 0;
//ui->stackedWidget->setCurrentIndex(PAGE_TRIP_SUMMARY);

void MainWindow::on_tripSummary_button_planEfficientTrip_clicked()
{
    the_trip_->resetTripCalc();
    db->ClearCart();
    ui->stackedWidget->setCurrentIndex(PAGE_PLAN_REGULAR_TRIP);
}

void MainWindow::on_tripSummary_button_goMainMenu_clicked()
{
    the_trip_->resetTripCalc();
    db->ClearCart();
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);
}


void MainWindow::on_pageSummary_button_mainMenu_clicked()
{
    the_trip_->resetTripCalc();
    db->ClearCart();
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);
    ui->tripSummary_label_totalDistanceTraveledValue->clear();
}

void MainWindow::on_tripSummary_button_planCustomTrip_clicked()
{
    the_trip_->resetTripCalc();
    db->ClearCart();
    initializeCustomTripPage();
    ui->stackedWidget->setCurrentIndex(PAGE_PLAN_CUSTOM_TRIP);
    ui->tripSummary_label_totalDistanceTraveledValue->clear();
}
