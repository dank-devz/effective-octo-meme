#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include "database.h"
#include "restauranttablemodel.h"
#include "menutablemodel.h"
#include "carttablemodel.h"
#include "trip.h"
#include "adminlogin.h"
#include "additemspopup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum pageNames
    {
        PAGE_HOME = 0,
        PAGE_VIEW_ALL_RESTAURANTS = 1,
        PAGE_PLAN_REGULAR_TRIP = 2,
        PAGE_PLAN_CUSTOM_TRIP = 3,
        PAGE_VIEW_DETAILS = 4,
        PAGE_CART_ITEMS = 5,
        PAGE_TRIP_SUMMARY = 6
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Trip* getTrip(QVector<int> ids);

signals:
    void adminStatusChanged(bool isAdmin);

public slots:
    void toggleAdminFeatures(bool isAdmin);
    void AddMenuItem(int restID, QString name, double price);

private slots:
    /*
     * T O O L B A R  F U N C T I O N S
     */
    void on_actionQuit_triggered();
    void on_actionLogin_triggered();
    void on_actionLogout_triggered();

    /*
     * H O M E  P A G E  F U N C T I O N S
     */
    void on_home_pushButton_viewAllRestaurants_clicked();
    void on_home_pushButton_planRegularFoodRun_clicked();
    void on_home_pushButton_planCustomFoodRun_clicked();

    /*
     * V I E W  A L L  R E S T A U R A N T  F U N C T I O N S
     */
    void on_viewAllRestaurants_pushButton_back_clicked();
    void on_viewAllRestaurants_pushButton_viewDetails_clicked();//inc

    /*
     * P L A N  R E G U L A R  T R I P  F U N C T I O N S
     */
    void on_planRegularTrip_pushButton_back_clicked();
    void on_planRegularTrip_pushButton_go_clicked();

    /*
     * P L A N  C U S T O M  T R I P  F U N C T I O N S
     */
    void on_planCustomFoodRun_pushButton_back_clicked();

    /*
     * V I E W  D E T A I L S  F U N C T I O N S
     */
    void on_viewDetails_pushButton_back_clicked();

    /*
     * C A R T  F U N C T I O N S
     */
    void on_cartItems_addSelected_clicked();
    void on_cartItems_pushButton_Back_clicked();
    void on_cartItems_removeSelected_clicked();

    /*
     * O T H E R  F U N C T I O N S
     */
    void initViewAllRestaurantsTable();
    void initViewDetailsTable(int id);
    void initCartItemsTable(int id);
    void adminButtonsShow();
    void adminButtonsHide();

    void on_cartItems_pushButton_next_clicked();

    void on_admin_submitChanges_menu_pushButton_clicked();

    void on_admin_submitChanges_restaurant_pushButton_clicked();
    void on_pushButton_clicked();

    void on_admin_viewAllRestaurants_addRestaurant_pushButton_clicked();

    void on_admin_viewAllRestaurants_removeRestaurant_pushButton_clicked();

    void on_admin_viewDetails_removeMenuItem_pushButton_clicked();

    void on_admin_viewDetails_addMenuItem_pushButton_clicked();

private:

    void initializeAdminFeatures();
    double cartTotal;

    Ui::MainWindow *ui;
    Trip *the_trip_;  //< Pointer to a trip variable to hold trip data

    /*
     * O T H E R  V A R I A B L E S
     */

    MenuTableModel *menuModel;
    RestaurantTableModel *restaurantModel;
    CartTableModel *cartModel;
    Database *db;
};

#endif // MAINWINDOW_H
