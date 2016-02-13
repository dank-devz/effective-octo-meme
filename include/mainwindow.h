#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionQuit_triggered();

    void on_home_pushButton_viewAllRestaurants_clicked();

    void on_home_pushButton_planRegularFoodRun_clicked();

    void on_home_pushButton_planCustomFoodRun_clicked();

    void on_viewAllRestaurants_pushButton_back_clicked();

    void on_viewAllRestaurants_pushButton_viewDetails_clicked();//inc

    void on_planRegularTrip_pushButton_back_clicked();

    void on_planCustomFoodRun_pushButton_back_clicked();

    void on_viewDetails_pushButton_back_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
