#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // sets the default page to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_viewAllRestaurants_clicked()
{
    // takes the user to the viewAllRestaurants page (index - 1)
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_planRegularFoodRun_clicked()
{
    // takes the user to the planRegularFoodRun page (index - 2)
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_planCustomFoodRun_clicked()
{
    // takes the user to the planCustomFoodRun page (index - 3)
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_back1_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_back2_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_back3_clicked()
{
    // takes the user back to the home page (index - 0)
    ui->stackedWidget->setCurrentIndex(0);
}
