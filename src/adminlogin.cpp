#include "adminlogin.h"
#include "ui_adminlogin.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}
AdminLogin::AdminLogin(QWidget *parent, bool *isValidPassword) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_pushButton_cancel_clicked()
{
    QWidget::close();
}

void AdminLogin::on_pushButton_ok_clicked()
{
//    if()
//    {
//        isValidPassword_ =  true;
//        QWidget::close();
//    }
}
