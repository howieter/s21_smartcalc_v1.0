#ifndef SMART_CALC_H
#define SMART_CALC_H

#include "ui_smart_calc.h"
#include "qcustomplot.h"
#include <QVector>
#include <QShortcut>
#include "menu.h"

#define numspace(x, a, b) (x >= a && x <= b)

extern "C" {
    #include "s21_smart_calc.h"
}

class smart_calc : public QWidget
{
    Q_OBJECT

public:
    explicit smart_calc(QWidget *parent = nullptr);
    ~smart_calc();

    double polish_notation_C(QString str);

    // graph methods
    void show_graph();
    void hide_graph();
    void draw_graph(QString str);
private:
    Ui::smart_calc *ui;

private:
    // shortcuts
    void shortcuts();

private:
    // support methods
    int OperSpace(QPushButton *pressedButton);
    void Cursor_to_the_End();
    void Change_Oper();
    int count_of_chars_to_space();
    void some_backspaces(int i);
    int FindPoint();
    int put_mul_find_mistakes(QString* str);


    double xBegin, xEnd, h, X;
    int N;
    QVector<double> x, y;

private slots:
    // buttons
    void OperPressed();
    void EqualButton();
    void All_Clear();
    void Single_Clear();
    void Num_Sign();
    void xButton_clicked();
};
#endif // SMART_CALC_H
