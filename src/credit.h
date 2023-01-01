#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
#include "smart_calc.h"
#include "deposit.h"
#include <string.h>

extern "C" {
    #include "s21_smart_calc.h"
}

namespace Ui {
class credit;
}

class credit : public QWidget
{
    Q_OBJECT

public:
    explicit credit(QWidget *parent = nullptr);
    ~credit();

private slots:
    void on_calculate_clicked();

    void on_clear_clicked();

    void on_lineEdit_money_editingFinished();

private:
    Ui::credit *ui;
};

#endif // CREDIT_H
