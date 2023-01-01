#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum {
    NOT_A_NUM = -69,
    STACK_UNDERFLOW = -1,
    STACK_OVERFLOW = -256,

    SUM = 43,
    SUB = 45,
    UNAR_SUB = 126,
    MUL = 42,
    DIV = 47,
    MOD = 37,
    SQR = 94,
    SQRT = 62,
    SIN = 115,
    ASIN = 83,
    COS = 99,
    ACOS = 67,
    TAN = 116,
    ATAN = 84,
    LOG = 108,
    LN = 76,

    BRACKET_LEFT = 40,
    BRACKET_RIGHT = 41,
};

typedef struct Node {
    long double value;
    int index;
    int priority;
    struct Node *next;
} Node;

void push(Node **top, long double val);
long double pop(Node **top);
int oper_define(char* str);
int priority(int oper, Node** nums);
void operation(Node** nums, Node** opers);
void priority_compare(Node** nums, Node** opers, int current_oper_prior);
double parser(const char** str);

int is_num(const char* str);
long long int atoi_p(const char** str);
long double atof_p(const char** str);

#endif // S21_SMART_CALC_H
