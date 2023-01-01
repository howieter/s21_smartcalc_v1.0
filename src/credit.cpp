#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
    on_lineEdit_money_editingFinished();
}

credit::~credit()
{
    delete ui;
}

void credit::on_calculate_clicked()
{
    uint money = ui->lineEdit_money->text().toInt();
    double rate = point_pars(ui->lineEdit_rate->text()).toDouble();
    uint period = ui->lineEdit_period->text().toInt();
    double monthly = 0.0;
    double overpay = 0.0;
    double total   = 0.0;
    if (ui->comboBox->currentText() == "Annuity") {
        rate = rate / (12.0 * 100.0);
        monthly = money * (rate / (1 - 1 / (pow(1 + rate, period))));
        overpay = monthly * period - money;
        total = money + overpay;
    } else if (ui->comboBox->currentText() == "Differentiated") {
        double monthly_no_percent = money / period;
        double credit_percent = 0.0;
        for (uint i = 0; i < period; i++) {
            credit_percent = (money - (monthly_no_percent * i)) * rate / 100 * 30.5 / 365.0;
            monthly = monthly_no_percent + credit_percent;
            total += monthly;
        }
        overpay = total - money;
    }
    ui->lineEdit_monthly->setText(QString::number(monthly));
    ui->lineEdit_overpayment->setText(QString::number(overpay));
    ui->lineEdit_total->setText(QString::number(total));
}

void credit::on_clear_clicked()
{
    ui->lineEdit_money->clear();
    ui->lineEdit_rate->clear();
    ui->lineEdit_period->clear();
    ui->lineEdit_monthly->clear();
    ui->lineEdit_overpayment->clear();
    ui->lineEdit_total->clear();
}

void credit::on_lineEdit_money_editingFinished()
{
    ui->lineEdit_money->setValidator(new QIntValidator(0, 2000000000, this));
    ui->lineEdit_period->setValidator(new QIntValidator(0, 2000000000, this));
    ui->lineEdit_rate->setValidator(new QDoubleValidator(0, 0, 5, this));
}

