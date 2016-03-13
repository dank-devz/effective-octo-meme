#include "include/mainwindow.h"
#include "include/adminlogin.h"
#include "ui_mainwindow.h"
#include <iostream>

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
    ui->planRegularTrip_comboBox_numberOfStops->hide();
    ui->planRegularTrip_label_promptLocations->hide();
    initViewAllRestaurantsTable(db);
    isAdmin = false;
    QObject::connect(this, SIGNAL(adminStatusChanged(bool)),
                     this, SLOT(initializeAdminButtons(bool)));
    ui->admin_submitChanges_menu_pushButton->setVisible(false);
    ui->tableView->setEditTriggers(0);
}

MainWindow::~MainWindow()
{
    db->ClearCart();
    delete ui;
}

void MainWindow::setAdminStatus(bool isAdmin)
{
    qDebug() << "SLOT!!";
    this->isAdmin = isAdmin;
}

void MainWindow::initializeAdminButtons(bool isAdmin)
{
    this->isAdmin = isAdmin;

    if(isAdmin)
    {
        ui->tableView->setEditTriggers(QTableView::DoubleClicked);
    }
    else
    {
        ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    }
    ui->admin_submitChanges_menu_pushButton->setEnabled(isAdmin);
    ui->admin_submitChanges_menu_pushButton->setVisible(isAdmin);
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
    for(int i = 0; i < restaurants.size(); i ++)
    {
        ui->planRegularTrip_comboBox_numberOfStops->addItem(QString::number(i+1));
        ui->planRegularTrip_comboBox_startingLocation->addItem(restaurants.at(i));
    }
}

void MainWindow::on_home_pushButton_planCustomFoodRun_clicked()
{
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
    // takes the user to the view details page
    ui->stackedWidget->setCurrentIndex(PAGE_VIEW_DETAILS);

    // Get the information for the currently selected item
    int currentRow         = ui->viewAllRestaurants_tableView->currentIndex().row();
    QModelIndex nameIndex  = ui->viewAllRestaurants_tableView->model()->index(currentRow, 1);
    QModelIndex idIndex    = ui->viewAllRestaurants_tableView->model()->index(currentRow, 0);

    // Get the Restaurant name and location ID
    int locationID = ui->viewAllRestaurants_tableView->model()->data(idIndex).toInt();
    QString Title  = ui->viewAllRestaurants_tableView->model()->data(nameIndex).toString() + "'s Menu";
    qDebug() << "Showing Menu for Location " << locationID << ", " << Title;

    // Fill the view with the infos
    ui->label->setText(Title);
    initViewDetailsTable(db, currentRow+1);
    ui->tableView->hideColumn(0);
    ui->viewAllRestaurants_tableView->resizeColumnsToContents();
}

void MainWindow::on_planRegularTrip_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(PAGE_HOME);

    // cleares the combo boxes
    ui->planRegularTrip_comboBox_numberOfStops->clear();
    ui->planRegularTrip_comboBox_startingLocation->clear();
}

// WILL BE REPLACED
void MainWindow::on_planRegularTrip_pushButton_go_clicked()
{
    // takes the user to the view details page
    ui->stackedWidget->setCurrentIndex(PAGE_CART_ITEMS);

//    // Get the information for the currently selected item
//    int currentRow         = ui->viewAllRestaurants_tableView->currentIndex().row();
//    QModelIndex nameIndex  = ui->viewAllRestaurants_tableView->model()->index(currentRow, 1);
//    QModelIndex idIndex    = ui->viewAllRestaurants_tableView->model()->index(currentRow, 0);

//    // Get the Restaurant name and location ID
    int locationID = db->GetRestaurantId(ui->planRegularTrip_comboBox_startingLocation->currentText());//ui->viewAllRestaurants_tableView->model()->data(idIndex).toInt();
    QString Title  = ui->planRegularTrip_comboBox_startingLocation->currentData().toString();//ui->viewAllRestaurants_tableView->model()->data(nameIndex).toString() + "'s Menu";
    qDebug() << "Showing Menu for Location " << locationID << ", " << Title;

    // Fill the view with the infos
    ui->label->setText(Title);
    ui->cartItems_label_restaurant_name->setText(ui->planRegularTrip_comboBox_startingLocation->currentText() + " Menu");
    initCartItemsTable(db, locationID);
    ui->cartItems_tableView_items->hideColumn(MenuTableModel::ID);
    ui->cartItems_tableView_items->resizeColumnsToContents();
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

void MainWindow::initViewAllRestaurantsTable(Database *db)
{
    restaurantModel = new RestaurantTableModel(this, db);
    ui->viewAllRestaurants_tableView->setModel(restaurantModel);
    ui->viewAllRestaurants_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->viewAllRestaurants_tableView->resizeColumnsToContents();
}

void MainWindow::initViewDetailsTable(Database *db, int id)
{
    menuModel = new MenuTableModel(this, db, id);
    ui->tableView->setModel(menuModel);
    qDebug() << "isAdmin: " << isAdmin;
    ui->viewAllRestaurants_tableView->resizeColumnsToContents();
}

void MainWindow::initCartItemsTable(Database *db, int id)
{
    menuModel = new MenuTableModel(this, db, id);
    cartModel = new CartTableModel(this, db);
    ui->cartItems_tableView_items->setModel(menuModel);
    ui->cartItems_tableView_items->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartItems_tableView_items->hideColumn(MenuTableModel::ITEMID);
    ui->cartItems_tableView_items->resizeColumnsToContents();
    ui->cartItems_tableView_reciept->setModel(cartModel);
    ui->cartItems_tableView_reciept->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cartItems_tableView_reciept->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_cartItems_addSelected_clicked()
{

    // Get the information for the currently selected item
    int currentRow          = ui->cartItems_tableView_items->currentIndex().row();
    QModelIndex nameIndex   = ui->cartItems_tableView_items->model()->index(currentRow, 1);
    QModelIndex itemIdIndex = ui->cartItems_tableView_items->model()->index(currentRow, 3);

    // Get the Restaurant name and location ID
    int itemID = ui->cartItems_tableView_items->model()->data(itemIdIndex).toInt();
    QString itemName  = ui->cartItems_tableView_items->model()->data(nameIndex).toString();
    int quantity = ui->cartItems_spinBox_quantity->value();
    db->PurchaseItem(itemID, quantity);
    cartModel->select();
    ui->cartItems_label_totalValue->setText("$" + QString::number(db->GetCartTotal()));
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

}

void MainWindow::on_actionLogin_triggered()
{
    AdminLogin *adminPrompt;
    adminPrompt = new AdminLogin(this, db);
    QObject::connect(adminPrompt, SIGNAL(adminStatusChanged(bool)),
                     this, SLOT(initializeAdminButtons(bool)));
    adminPrompt->setWindowModality(Qt::ApplicationModal);
    adminPrompt->show();

}

void MainWindow::on_actionLogout_triggered()
{
     emit adminStatusChanged(false);
}

void MainWindow::adminButtonsShow()
{

}

void MainWindow::adminButtonsHide()
{

}

void MainWindow::on_cartItems_pushButton_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(PAGE_TRIP_SUMMARY);
}

void MainWindow::on_admin_submitChanges_pushButton_clicked()
{
    menuModel->submitAll();
    qDebug() << "Changes to menu table have been made.";
}
