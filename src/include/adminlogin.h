#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = 0);
    explicit AdminLogin(QWidget *parent = 0, bool *isValidPassword = false, Database *database = NULL);
    ~AdminLogin();

private slots:
    // closes the window
    void on_pushButton_cancel_clicked();
    // checks to see if the password is correct
    void on_pushButton_ok_clicked();

private:
    Ui::AdminLogin *ui;
    bool isValidPassword_;
    Database*  database_;
};

#endif // ADMINLOGIN_H
