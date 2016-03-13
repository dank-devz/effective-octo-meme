#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = 0);
    explicit AdminLogin(QWidget *parent = 0, bool *isValidPassword = false);
    ~AdminLogin();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::AdminLogin *ui;
    bool isValidPassword_;
};

#endif // ADMINLOGIN_H
