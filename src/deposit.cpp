#include "deposit.h"
#include "ui_deposit.h"

deposit::deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deposit)
{
    ui->setupUi(this);
    ui->lineEdit_replenish->hide();
}

deposit::~deposit()
{
    delete ui;
}

void deposit::on_lineEdit_dep_editingFinished()
{
    ui->lineEdit_dep->setValidator(new QIntValidator(0, 2000000000, this));
    ui->lineEdit_period->setValidator(new QIntValidator(0, 2000000000, this));
    ui->lineEdit_rate->setValidator(new QDoubleValidator(0, 0, 5, this));
    ui->lineEdit_key_rate->setValidator(new QDoubleValidator(0, 0, 5, this));
    ui->lineEdit_tax_kind->setValidator(new QDoubleValidator(0, 0, 5, this));
    ui->lineEdit_replenish->setValidator(new QDoubleValidator(0, 0, 5, this));
}


void deposit::on_pushButton_2_clicked()
{
    ui->lineEdit_dep->clear();
    ui->lineEdit_period->clear();
    ui->lineEdit_rate->clear();
    ui->lineEdit_key_rate->clear();
    ui->lineEdit_tax_kind->clear();
    ui->lineEdit_am_money->clear();
    ui->lineEdit_am_rate->clear();
    ui->lineEdit_am_tax->clear();
    ui->lineEdit_replenish->clear();
}


void deposit::on_pushButton_clicked()
{
    account_t new_acc;
    new_acc.money = ui->lineEdit_dep->text().toInt();
    new_acc.period = ui->lineEdit_period->text().toInt();
    new_acc.rate = point_pars(ui->lineEdit_rate->text()).toDouble();
    new_acc.key_rate = point_pars(ui->lineEdit_key_rate->text()).toDouble();
    new_acc.capitalisation = ui->box_capitalisation->currentText();
    new_acc.payout = ui->box_payout->currentText();
    new_acc.replenishment = ui->box_replenishment->currentText();
    new_acc.tax_kind = point_pars(ui->lineEdit_tax_kind->text()).toDouble();
    if (ui->lineEdit_replenish->isVisible()) {
        new_acc.replenish = point_pars(ui->lineEdit_replenish->text()).toDouble();
    }


    new_acc.percent = 0;
    new_acc.deposit = new_acc.money;
    new_acc.tax = 0;

    if (new_acc.capitalisation == "No") {
        no_capitalisation(&new_acc);
    } else {
        capitalisation(&new_acc);
    }

    ui->lineEdit_am_money->setText(QString::number(new_acc.deposit));
    ui->lineEdit_am_rate->setText(QString::number(new_acc.percent));
    ui->lineEdit_am_tax->setText(QString::number(new_acc.tax));
}

void deposit::capitalisation(account_t* acc) {
    int cap_frequency = combo_box_pars(acc->capitalisation);

    int add_frequency = 0;
    if (acc->replenishment != "No") {
        add_frequency = combo_box_pars(acc->replenishment);
    }
    for (int i = cap_frequency; i <= acc->period; i += cap_frequency) {
        if (acc->replenishment != "No" && i >= add_frequency) {
            acc->deposit += acc->replenish;
        }
        acc->deposit += procent_calc(acc->deposit, acc->rate, cap_frequency);
    }
    acc->percent = acc->deposit - acc->money;
}

void deposit::no_capitalisation(account_t* acc) {
    acc->percent = procent_calc(acc->money, acc->rate, acc->period);
    acc->deposit = acc->money + acc->percent;
    if (acc->replenishment != "No") {
        replenish_calc_noCap(acc);
    }
    if (acc->rate > acc->key_rate) {
        tax_calculate(acc);
    }
}

void deposit::tax_calculate(account_t* acc) {
    double tax_dif = 0;
    tax_dif = procent_calc(acc->money, acc->key_rate, acc->period);
    acc->tax = acc->tax_kind / 100.0 * (acc->percent - tax_dif);
    acc->percent -= acc->tax;
    acc->deposit -= acc->tax;
}

void deposit::replenish_calc_noCap(account_t* acc) {
    int add_frequency = combo_box_pars(acc->replenishment);;
    double added_percent = 0;
    int dop_invest = 0;
    for (int i = add_frequency; i < acc->period; i += add_frequency) {
        dop_invest += acc->replenish;
        added_percent += procent_calc(acc->replenish, acc->rate, i);
    }
    acc->percent += added_percent;
    acc->deposit += added_percent + dop_invest;
}

double deposit::procent_calc(int money, double rate, int period) {
    return money * rate / 100.0 * period * MONTH / 365;
}

QString point_pars(QString str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
    return str;
}
                                                            // Д - доход по вкладу (percent)
int deposit::combo_box_pars(QString str) {                  // С - вкладываемые деньги (deposit)
    int value = 0;
    if (str == "Monthly") {                                 // П - размер ставки (rate)
        value = 1;                                          // К - количество дней вклада (period)
    } else if (str == "6 months") {                         // Кг - дней в году (365)
        value = 6;
    } else if (str == "1 year") {
        value = 12;
    }
    return value;
}

void deposit::on_box_replenishment_currentTextChanged(const QString &arg1)
{
    if (arg1 == "No") {
        ui->lineEdit_replenish->hide();
    } else {
        ui->lineEdit_replenish->show();
    }
}

