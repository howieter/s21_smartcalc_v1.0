#include "menu.h"
#include "ui_menu.h"


menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+1"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_Calculator_triggered()));

    shortcut = new QShortcut(QKeySequence("Ctrl+2"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_Graph_triggered()));

    shortcut = new QShortcut(QKeySequence("Ctrl+3"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_Credit_triggered()));

    shortcut = new QShortcut(QKeySequence("Ctrl+4"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_Deposit_triggered()));

}

menu::~menu()
{
    delete ui;
}

void menu::on_Calculator_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    QWidget *widget = ui->stackedWidget->currentWidget();
    smart_calc *smartCalc = qobject_cast<smart_calc *>(widget);
    if (smartCalc)
    {
        smartCalc->hide_graph();
        resize(800, 150);
    }
}

void menu::on_Graph_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    QWidget *widget = ui->stackedWidget->currentWidget();
    smart_calc *smartCalc = qobject_cast<smart_calc *>(widget);
    if (smartCalc)
    {
        smartCalc->show_graph();
        resize(800, 600);
    }

}

void menu::on_Credit_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    resize(829, 280);
}


void menu::on_Deposit_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
    resize(729, 420);
}
