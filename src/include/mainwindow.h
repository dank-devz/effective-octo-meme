#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "restauranttablemodel.h"
#include "menutablemodel.h"
#include "carttablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /*
     * T O O L B A R  F U N C T I O N S
     */
    void on_actionQuit_triggered();

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
     * O T H E R  F U N C T I O N S
     */
    void initViewAllRestaurantsTable(Database *db);
    void initViewDetailsTable(Database *db, int id);
    void initCartItemsTable(Database *db, int id);

    void on_cartItems_addSelected_clicked();

private:
    Ui::MainWindow *ui;

    /*
     * D A T A B A S E  V A R I A B L E S
     */

    MenuTableModel *menuModel;
    RestaurantTableModel *restaurantModel;
    CartTableModel *cartModel;
    Database *db;
};

#endif // MAINWINDOW_H
