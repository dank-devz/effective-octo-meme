#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // sets the default page to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);

    // instantiate the database and the model
    db = new Database();
    initViewAllRestaurantsTable(db);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_home_pushButton_viewAllRestaurants_clicked()
{
    // takes the user to the viewAllRestaurants page (index - 1)
    ui->stackedWidget->setCurrentIndex(1);
    ui->viewAllRestaurants_tableView->hideColumn(0);
}

void MainWindow::on_home_pushButton_planRegularFoodRun_clicked()
{
    // takes the user to the planRegularFoodRun page (index - 2)
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_home_pushButton_planCustomFoodRun_clicked()
{
    // takes the user to the planCustomFoodRun page (index - 3)
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_viewAllRestaurants_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_viewAllRestaurants_pushButton_viewDetails_clicked()
{
    // takes the user to the view details page
    ui->stackedWidget->setCurrentIndex(4);

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
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_planCustomFoodRun_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_viewDetails_pushButton_back_clicked()
{
    // takes the user back to the viewAllRestaurants page (index - 1)
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::initViewAllRestaurantsTable(Database *db)
{
    RestaurantTableModel *resTableModel = new RestaurantTableModel(this, db);
    ui->viewAllRestaurants_tableView->setModel(resTableModel);
    ui->viewAllRestaurants_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->viewAllRestaurants_tableView->resizeColumnsToContents();
}

void MainWindow::initViewDetailsTable(Database *db, int id)
{
    MenuTableModel *resMenuModel = new MenuTableModel(this, db, id);
    ui->tableView->setModel(resMenuModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->viewAllRestaurants_tableView->resizeColumnsToContents();
}
