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


/*
 * T O O L B A R  F U N C T I O N S
 */
void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


/*
 * H O M E  P A G E  F U N C T I O N S
 */
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


/*
 * V I E W  A L L  R E S T A U R A N T  F U N C T I O N S
 */
void MainWindow::on_viewAllRestaurants_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_viewAllRestaurants_pushButton_viewDetails_clicked()
{
    // takes the user to the view details page
    ui->stackedWidget->setCurrentIndex(4);

    // get the information for the currently selected item
    int currentRow         = ui->viewDetails_tableView->currentIndex().row();
    QModelIndex nameIndex  = ui->viewDetails_tableView->model()->index(currentRow, 1);
    QModelIndex idIndex    = ui->viewDetails_tableView->model()->index(currentRow, 0);

    // get the restaurant name and location ID
    int locationID = ui->viewDetails_tableView->model()->data(idIndex).toInt();
    QString Title  = ui->viewDetails_tableView->model()->data(nameIndex).toString() + "'s Menu";
    qDebug() << "Showing Menu for Location " << locationID << ", " << Title;

    // Fill the view with the infos
    ui->viewDetails_label_title->setText(Title);
    initViewDetailsTable(db, currentRow+1);
    ui->viewDetails_tableView->hideColumn(0);
}


/*
 * P L A N  R E G U L A R  T R I P  F U N C T I O N S
 */
void MainWindow::on_planRegularTrip_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}


/*
 * P L A N  C U S T O M  T R I P  F U N C T I O N S
 */
void MainWindow::on_planCustomFoodRun_pushButton_back_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}


/*
 * V I E W  D E T A I L S  F U N C T I O N S
 */
void MainWindow::on_viewDetails_pushButton_back_clicked()
{
    // takes the user back to the viewAllRestaurants page (index - 1)
    ui->stackedWidget->setCurrentIndex(1);
}


/*
 * O T H E R  F U N C T I O N S
 */
void MainWindow::initViewAllRestaurantsTable(Database *db)
{
    RestaurantTableModel *resTableModel = new RestaurantTableModel(this, db);
    ui->viewAllRestaurants_tableView->setModel(resTableModel);
    ui->viewAllRestaurants_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::initViewDetailsTable(Database *db, int id)
{
    MenuTableModel *resMenuModel = new MenuTableModel(this, db, id);
    ui->viewAllRestaurants_tableView->setModel(resMenuModel);
    ui->viewAllRestaurants_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
