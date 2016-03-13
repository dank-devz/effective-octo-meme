#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "database.h"

extern bool isAdmin = false;

AdminLogin::AdminLogin(QWidget *parent, Database *db) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    _database = db;
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_pushButton_ok_clicked()
{
    QString username = "dankdevz";
    if(_database->AuthenticateAdmin(username, ui->lineEdit_passwordForm->text()))
    {
        isAdmin = true;
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
