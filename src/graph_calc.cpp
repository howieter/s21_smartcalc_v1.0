#include "smart_calc.h"

void smart_calc::show_graph() {
    ui->label_Xmax->show();
    ui->label_Xmin->show();
    ui->label_Ymax->show();
    ui->label_Ymin->show();
    ui->lineEdit_Xmax->show();
    ui->lineEdit_Xmin->show();
    ui->lineEdit_Ymax->show();
    ui->lineEdit_Ymin->show();
    ui->widget_plot->show();
    ui->xButton->setText("x");
    ui->Equals->setText("draw");
}

void smart_calc::hide_graph() {
    ui->label_Xmax->hide();
    ui->label_Xmin->hide();
    ui->label_Ymax->hide();
    ui->label_Ymin->hide();
    ui->lineEdit_Xmax->hide();
    ui->lineEdit_Xmin->hide();
    ui->lineEdit_Ymax->hide();
    ui->lineEdit_Ymin->hide();
    ui->widget_plot->hide();
    ui->xButton->setText("copy");
    ui->Equals->setText("=");
}

void smart_calc::draw_graph(QString str) {
    ui->widget_plot->clearGraphs();
    double Xmin = ui->lineEdit_Xmin->text().toDouble();
    double Xmax = ui->lineEdit_Xmax->text().toDouble();
    double Ymin = ui->lineEdit_Ymin->text().toDouble();
    double Ymax = ui->lineEdit_Ymax->text().toDouble();


    if (Xmin <= -1000000) {
        xBegin = -1000000;
    } else {
        xBegin = Xmin;
    }
    if (Xmax >= 1000000) {
        xEnd = 1000000;
    } else {
        xEnd = Xmax;
    }
    h = 0.1;
    ui->widget_plot->xAxis->setRange(Xmin, Xmax);
    ui->widget_plot->yAxis->setRange(Ymin, Ymax);

    bool flag = false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'x') {
            flag = true;
            break;
        }
    }

    QString str_copy = ui->lineEdit->text();
    for (X = xBegin; X < xEnd; X += h) {
        x.push_back(X);
        if (flag == true) {
            str_copy = str;
            if (X > -0.1 && X < 0) {
                X = 0;
            }
            str_copy.replace('x', QString::number(X));
        }
        y.push_back(polish_notation_C(str_copy));
    }
    ui->widget_plot->addGraph();
    ui->widget_plot->graph(0)->addData(x, y);
    ui->widget_plot->replot();
    x.clear();
    y.clear();
}
