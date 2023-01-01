#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
#include <cmath>

#define MONTH   30.4166667

namespace Ui {
class deposit;
}

QString point_pars(QString str);

class deposit : public QWidget
{
    Q_OBJECT

private:
    typedef struct account_t {
        long long int money;
        int period;
        double rate, key_rate, tax_kind, replenish;
        QString payout, replenishment, capitalisation;
        double percent, tax;
        long long int deposit;
    } account_t;

public:
    explicit deposit(QWidget *parent = nullptr);
    ~deposit();

private slots:
    void on_lineEdit_dep_editingFinished();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    double procent_calc(int, double, int);

    void no_capitalisation(account_t* account);
    void capitalisation(account_t* acc);
    void tax_calculate(account_t* acc);
    void replenish_calc_noCap(account_t* acc);

    int combo_box_pars(QString str);

    void on_box_replenishment_currentTextChanged(const QString &arg1);

private:
    Ui::deposit *ui;
};

#endif // DEPOSIT_H
