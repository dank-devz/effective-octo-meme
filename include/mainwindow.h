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

    void on_pushButton_viewAllRestaurants_clicked();

    void on_pushButton_planRegularFoodRun_clicked();

    void on_pushButton_planCustomFoodRun_clicked();

    void on_pushButton_back1_clicked();

    void on_pushButton_back2_clicked();

    void on_pushButton_back3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
