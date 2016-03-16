#ifndef ADDITEMSPOPUP_H
#define ADDITEMSPOPUP_H

#include <QDialog>

namespace Ui {
class AddItemsPopup;
}

class AddItemsPopup : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemsPopup(QWidget *parent = 0, int restID = 420);
    ~AddItemsPopup();

signals:
    void MenuItemAdd(int, QString, double);

private slots:
    void on_AddItemsPopup_buttonBox_accepted();

private:
    Ui::AddItemsPopup *ui;
    int _restID;
};

#endif // ADDITEMSPOPUP_H
