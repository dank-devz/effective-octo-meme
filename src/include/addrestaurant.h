#ifndef ADDRESTAURANT_H
#define ADDRESTAURANT_H

#include <QDialog>
#include <QVector>

#include "database.h"

namespace Ui {
class addRestaurant;
}

/*
 * ENUM FOR ALL OF THE PAGES FOR THIS WINDOW
 */
enum pageNames
{
    PAGE_PRIMARY = 0,
    PAGE_ADD_ITEMS = 1,
    PAGE_ADD_DISTANCES = 2
};

class addRestaurant : public QDialog
{
    Q_OBJECT

public:
    /*
     * DEFAULT CONSTRUCTOR >>DON'T USE THIS ONE<<
     */
    explicit addRestaurant(QWidget *parent = 0);

    /*
     * CONSTRUCTOR FOR ADD NEW RESTAURANT
     */
    explicit addRestaurant(QWidget *parent = 0, Database *db = NULL);

    /*
     * CONSTRUCTOR FOR ADD NEW ITEMS TO EXISTING RESTAURANT
     */
    explicit addRestaurant(QWidget *parent = 0, int restaurantId_ = 0,  Database *db = NULL);
    ~addRestaurant();

private slots:
    /*
     * PAGE PRIMARY FUNCTIONS
     */
    void on_primary_lineEdit_name_textChanged(const QString &arg1);
    void on_primary_pushButton_cancel_clicked();
    void on_primary_pushButton_next_clicked();
    void on_primary_lineEdit_name_returnPressed();

    /*
     * PAGE ADD ITEMS FUNCTIONS
     */
    void on_addItems_pushButton_cancel_clicked();
    void on_addItems_pushButton_next_clicked();
    void on_addItems_pushButton_add_clicked();

    /*
     * PAGE ADD DISTANCES FUNCTIONS
     */
    void on_addDistances_pushButton_cancel_clicked();
    void on_addDistances_pushButton_next_clicked();
    
private:
    Ui::addRestaurant *ui;

    /*
     * FOR BOTH
     */
    Database *db_;                      //< the db that the data will be sent to

    /*
     * FOR ADD NEW RESTAURANT
     */
    QString restaurantName_;            //< stores the new restaurant name
    QVector<QString> menuItemNames_;    //< stores the new rautaurant menu item names
    QVector<double> menuItemPrices_;    //< stores the new reataurant menu item prices
    QVector<double> distances_;         //< stores the new restaurant distances to other locations

    QVector<int> otherLocations_;       //< the origional copy that's pased
    QVector<int> otherLocationsCopy_;   //< used to iterate through the list

    /*
     * FOR ADD MENU ITEM
     */
    int restaurantId_;                  //< stores the id of the restaurant that will have items added
};

#endif // ADDRESTAURANT_H
