#include "smart_calc.h"

smart_calc::smart_calc(QWidget *parent):
    QWidget(parent),
    ui(new Ui::smart_calc) {
    ui->setupUi(this);
    hide_graph();

    shortcuts();

    connect(ui->opr_0, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_1, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_2, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_3, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_4, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_5, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_6, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_7, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_8, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_9, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_sum, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_sub, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_mul, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_div, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_mod, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_cos, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_sin, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_tan, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_acos, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_asin, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_atan, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_log, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_ln, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_sqr, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_sqrt, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_bracket_left, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_bracket_right, SIGNAL(released()), this, SLOT(OperPressed()));
    connect(ui->opr_point, SIGNAL(released()), this, SLOT(OperPressed()));

    connect(ui->xButton, SIGNAL(released()), this, SLOT(xButton_clicked()));

    connect(ui->AllClear, SIGNAL(released()), this, SLOT(All_Clear()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(Single_Clear()));

    connect(ui->Sign, SIGNAL(released()), this, SLOT(Num_Sign()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
}

smart_calc::~smart_calc() {
    delete ui;
}


void smart_calc::OperPressed() {
    QPushButton *pressedButton = (QPushButton *)sender();

    if ((ui->lineEdit->text().right(2) == "+ " || ui->lineEdit->text().right(2) == "- " || ui->lineEdit->text().right(2) == "% " ||
         ui->lineEdit->text().right(2) == "/ " || ui->lineEdit->text().right(2) == "* " || ui->lineEdit->text().right(2) == "^ ") &&
        (pressedButton == ui->opr_sum || pressedButton == ui->opr_sub || pressedButton == ui->opr_mod ||
         pressedButton == ui->opr_div || pressedButton == ui->opr_mul || pressedButton == ui->opr_sqr)) {
        Change_Oper();
    } else if ((pressedButton == ui->opr_sum || pressedButton == ui->opr_sub || pressedButton == ui->opr_mod ||
                pressedButton == ui->opr_div || pressedButton == ui->opr_mul || pressedButton == ui->opr_point ||
                pressedButton == ui->opr_sqr) &&
               (ui->lineEdit->cursorPosition() == 0 || ui->lineEdit->text().right(1) == '(')) {

    } else if (pressedButton == ui->opr_point && FindPoint() == 1) {

    } else if (pressedButton == ui->opr_bracket_right &&
              (ui->lineEdit->cursorPosition() == 0 || ui->lineEdit->text().right(1) == ' ' || ui->lineEdit->text().right(1) == '(')) {

    } else if  (OperSpace(pressedButton) == 0) {
        ui->lineEdit->setText(ui->lineEdit->text() + pressedButton->text());
    } else {
            ui->lineEdit->setText(ui->lineEdit->text() + pressedButton->text());
            ui->lineEdit->setText(ui->lineEdit->text() + ' ');
    }

}

void smart_calc::All_Clear() {
    ui->lineEdit->clear();
}

void smart_calc::Single_Clear() {
    if (ui->lineEdit->cursorPosition() != 0 && ui->lineEdit->text()[ui->lineEdit->text().length() - 1] == '(') {
        some_backspaces(count_of_chars_to_space());
    } else if (ui->lineEdit->text().right(3) == " + " || ui->lineEdit->text().right(3) == " - " || ui->lineEdit->text().right(3) == " * " ||
               ui->lineEdit->text().right(3) == " / " || ui->lineEdit->text().right(3) == " % " || ui->lineEdit->text().right(3) == " ^ ") {
        some_backspaces(3);
    } else {
        ui->lineEdit->backspace();
    }
    ui->lineEdit->deselect();
}

void smart_calc::Num_Sign() {
    int i = ui->lineEdit->cursorPosition();
    while (true) {
        if (ui->lineEdit->text()[ui->lineEdit->cursorPosition()] == ')') {
            while (ui->lineEdit->text()[ui->lineEdit->cursorPosition()] != '(') {
                ui->lineEdit->cursorBackward(true);
            }
            ui->lineEdit->deselect();
        }
        if (i == 0 || ui->lineEdit->text()[ui->lineEdit->cursorPosition() - 1] == ' ' ||
                      ui->lineEdit->text()[ui->lineEdit->cursorPosition() - 1] == '(') {
            ui->lineEdit->setText(ui->lineEdit->text().insert(ui->lineEdit->cursorPosition(), '-'));
            Cursor_to_the_End();
            break;
        } else if (ui->lineEdit->text()[ui->lineEdit->cursorPosition() - 1] == '-') {
            ui->lineEdit->deselect();
            ui->lineEdit->backspace();
            Cursor_to_the_End();
            break;
        }
        ui->lineEdit->cursorBackward(true, 1);
        i--;
    }
    ui->lineEdit->deselect();
}

void smart_calc::Cursor_to_the_End() {
    int i = ui->lineEdit->cursorPosition();
    while (i < ui->lineEdit->text().length()) {
        ui->lineEdit->cursorForward(true, 1);
        i++;
    }
}

void smart_calc::Change_Oper() {
    QPushButton *pressedButton = (QPushButton *)sender();
    QString *btn = (QString *) pressedButton;
    if (ui->lineEdit->text()[ui->lineEdit->cursorPosition() - 2] != btn[0]) {
        some_backspaces(3);
        OperPressed();
    }
    Cursor_to_the_End();
}

int smart_calc::count_of_chars_to_space() {
    QChar curr_char;
    int count = 0;
    while (true) {
        curr_char = ui->lineEdit->text()[ui->lineEdit->cursorPosition()];
        if ((numspace(curr_char, '0', '9')) || curr_char == ' ') {
            count--;
            break;
        } else if (ui->lineEdit->cursorPosition() == 0) {
            break;
        }
        ui->lineEdit->cursorBackward(true, 1);
        count++;
    }
//    ui->lineEdit->setCursorPosition(ui->lineEdit->text().length());
    Cursor_to_the_End();
    return count;
}

void smart_calc::some_backspaces(int i) {
    for (int k = 0; k < i; k++) {
        ui->lineEdit->backspace();
    }
}

int smart_calc::OperSpace(QPushButton *pressedButton) {
    int flag = 0;
    if (pressedButton == ui->opr_sum || pressedButton == ui->opr_sub || pressedButton == ui->opr_mod ||
        pressedButton == ui->opr_div || pressedButton == ui->opr_mul || pressedButton == ui->opr_sqr) {
        ui->lineEdit->setText(ui->lineEdit->text() + ' ');
        flag = 1;
    }
    return flag;
}

int smart_calc::FindPoint() {
    QChar point = ui->lineEdit->text()[ui->lineEdit->cursorPosition()];
    int flag = 0;
    int count = 0;
    while (true) {
        if (point == '.') {
            flag = 1;
            break;
        } else if (ui->lineEdit->cursorPosition() == 0 || point == '(' || point == ' ') {
            break;
        }
        ui->lineEdit->cursorBackward(true);
        point = ui->lineEdit->text()[ui->lineEdit->cursorPosition()];
        count++;
    }
    Cursor_to_the_End();
    ui->lineEdit->deselect();
    return flag;
}

void smart_calc::EqualButton() {
    QString str = ui->lineEdit->text();
    int flag = put_mul_find_mistakes(&str);
    if (ui->Equals->text() == "=") {
        if (flag == 0) {
            ui->lineEdit->setText(QString::number(polish_notation_C(str)));
        }
    } else if (ui->Equals->text() == "draw") {
        if (flag == 0) {
            draw_graph(str);
        }
    }
    if (flag == -222) {
        QMessageBox::warning(this, "Syntax error", "You forgot the number after the last operator");
    } else if (flag > 0) {
        QMessageBox::warning(this, "Syntax error", "You forgot the closing parenthesis: " + QString::number(flag));
    }
}

double smart_calc::polish_notation_C(QString str) {
    const char* toCstr = str.toLatin1().data();
    return parser(&toCstr);
}

int smart_calc::put_mul_find_mistakes(QString* str) {
    int brackets_count = 0;
    for (int i = 0; i < str->length(); i++) {
        if ((*str)[i] == '(') {
            brackets_count++;
        } else if ((*str)[i] == ')') {
            brackets_count--;
        }
        if (str->right(1) == ' ' &&
                (str->right(2) == "+ " || str->right(2) == "- " || str->right(2) == "* " ||
                 str->right(2) == "/ " || str->right(2) == "^ " || str->right(2) == "% ")) {
            return -222;
        }
        if (i != str->length() - 1 && (((numspace((*str)[i], '0', '9') && (numspace((*str)[i + 1], 'a', 'z') || (*str)[i + 1] == '('))) ||
            (((*str)[i] == 'x' || (*str)[i] == ')') && (numspace((*str)[i + 1], '0', '9') ||
                                                        numspace((*str)[i + 1], 'a', 'z') || (*str)[i + 1] == '(')))) {
            str->insert(i + 1, " * ");
            put_mul_find_mistakes(str);
        }
    }
    if (brackets_count != 0) {
        return brackets_count;
    }
    return 0;
}

void smart_calc::xButton_clicked()
{
    if (ui->xButton->text() == "x") {
        OperPressed();
    } else if (ui->xButton->text() == "copy") {
        ui->lineEdit->selectAll();
        ui->lineEdit->copy();
        ui->lineEdit->deselect();
    }
}

void smart_calc::shortcuts() {
    QObject::connect(new QShortcut(Qt::Key_0, ui->opr_0), &QShortcut::activated, [this](){ ui->opr_0->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_1, ui->opr_1), &QShortcut::activated, [this](){ ui->opr_1->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_2, ui->opr_2), &QShortcut::activated, [this](){ ui->opr_2->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_3, ui->opr_3), &QShortcut::activated, [this](){ ui->opr_3->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_4, ui->opr_4), &QShortcut::activated, [this](){ ui->opr_4->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_5, ui->opr_5), &QShortcut::activated, [this](){ ui->opr_5->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_6, ui->opr_6), &QShortcut::activated, [this](){ ui->opr_6->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_7, ui->opr_7), &QShortcut::activated, [this](){ ui->opr_7->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_8, ui->opr_8), &QShortcut::activated, [this](){ ui->opr_8->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_9, ui->opr_9), &QShortcut::activated, [this](){ ui->opr_9->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Comma, ui->opr_point), &QShortcut::activated, [this](){ ui->opr_point->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Period, ui->opr_point), &QShortcut::activated, [this](){ ui->opr_point->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Plus, ui->opr_sum), &QShortcut::activated, [this](){ ui->opr_sum->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Minus, ui->opr_sub), &QShortcut::activated, [this](){ ui->opr_sub->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Slash, ui->opr_div), &QShortcut::activated, [this](){ ui->opr_div->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Percent, ui->opr_mod), &QShortcut::activated, [this](){ ui->opr_mod->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Asterisk, ui->opr_mul), &QShortcut::activated, [this](){ ui->opr_mul->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Return, ui->Equals), &QShortcut::activated, [this](){ ui->Equals->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Enter, ui->Equals), &QShortcut::activated, [this](){ ui->Equals->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Backspace, ui->Clear), &QShortcut::activated, [this](){ ui->Clear->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_Delete, ui->AllClear), &QShortcut::activated, [this](){ ui->AllClear->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_AsciiCircum, ui->opr_sqr), &QShortcut::activated, [this](){ ui->opr_sqr->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_ParenRight, ui->opr_bracket_right), &QShortcut::activated, [this](){ ui->opr_bracket_right->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_ParenLeft, ui->opr_bracket_left), &QShortcut::activated, [this](){ ui->opr_bracket_left->animateClick(); });
    QObject::connect(new QShortcut(Qt::Key_X, ui->xButton), &QShortcut::activated, [this](){ ui->xButton->animateClick(); });


}
