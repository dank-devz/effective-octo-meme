#ifndef ADDRESTAURANT_H
#define ADDRESTAURANT_H

#include <QDialog>
#include <QVector>

#include "database.h"

namespace Ui {
class addRestaurant;
}

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
    explicit addRestaurant(QWidget *parent = 0);
    explicit addRestaurant(QWidget *parent = 0, Database *db = NULL);
    explicit addRestaurant(QWidget *parent = 0, int restaurantId_ = 0,  Database *db = NULL);
    ~addRestaurant();

private slots:

    void on_primary_lineEdit_name_textChanged(const QString &arg1);

    void on_primary_pushButton_cancel_clicked();

    void on_primary_pushButton_next_clicked();

    void on_primary_lineEdit_name_returnPressed();

    void on_addItems_pushButton_cancel_clicked();

    void on_addItems_pushButton_next_clicked();

    void on_addItems_pushButton_add_clicked();

private:
    Ui::addRestaurant *ui;

    /*
     *  O T H E R  V A R I A B L E S
     */
    Database *db_;
    QString restaurantName_;
    QVector<QString> menuItemNames_;
    QVector<double> menuItemPrices_;
    QVector<double> distances_;

    /*
     * F O R  A D D  M E N U  I T E M
     */
    int restaurantId_;
};

#endif // ADDRESTAURANT_H
