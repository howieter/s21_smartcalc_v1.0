#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "smart_calc.h"
#include "credit.h"
#include "deposit.h"
#include <QWidget>
#include <QSize>

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_Calculator_triggered();
    void on_Graph_triggered();
    void on_Credit_triggered();
    void on_Deposit_triggered();

private:
    Ui::menu *ui;
};

#endif // MENU_H
