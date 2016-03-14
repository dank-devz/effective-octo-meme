#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "database.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}
AdminLogin::AdminLogin(QWidget *parent, bool *isValidPassword, Database *database) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Admin Login");

    // sets the private variables to the passed in parameters
    isValidPassword_ = isValidPassword;
    database_ = database;
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_pushButton_ok_clicked()
{
    QString username = "dankdevz";
    if(database_->AuthenticateAdmin(username, ui->lineEdit_passwordForm->text()))
    {
        isValidPassword_ =  true;
        QWidget::close();
    }
    else
    {
        ui->label_errorMessage->setText("Invalid Password");
    }
}

void AdminLogin::on_pushButton_cancel_clicked()
{
    QWidget::close();
}
