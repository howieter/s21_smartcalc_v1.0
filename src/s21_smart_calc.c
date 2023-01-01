#include "s21_smart_calc.h"

void push(Node **top, long double val) {
    if ((*top)->index == 255) {
        exit(STACK_OVERFLOW);
    }
    Node *new = (Node*)calloc(1, sizeof(Node));
    new->index = (*top)->index + 1;
    new->value = val;
    new->next = (*top);
    (*top) = new;
}

long double pop(Node **top) {
    if ((*top)->index == 0) {
        exit(STACK_UNDERFLOW);
    }
    Node* prev = NULL;
    long double val = 0;
    prev = (*top);
    val = prev->value;
    (*top) = (*top)->next;

    free(prev);
    return val;
}

int is_num(const char* str) {
    return *str >= '0' && *str <= '9' ? *str : NOT_A_NUM;
}

long long int atoi_p(const char** str) {
    long long int res = 0;
    while (*str[0] <= '9' && *str[0] >= '0') {
        res = 10 * res + (*str[0]++ - '0');
    }
    return res;
}

long double atof_p(const char** str) {
    long double int_part = atoi_p(str);
    long double float_part = 0;
    int float_part_length = 0;
    if (*str[0] == '.') {
        str[0]++;
        while (*str[0] <= '9' && *str[0] >= '0') {
            float_part = 10 * float_part + (*str[0]++ - '0');
            float_part_length++;
        }
    }
    return int_part + float_part / pow(10, float_part_length);
}

int oper_define(char* str) {
    int define = 0;
    if (!strcmp(str, " + " )) { define = SUM; }
    else if (!strcmp(str, " - ")) { define = SUB; }
    else if (!strcmp(str, "-")) { define = UNAR_SUB; }
    else if (!strcmp(str, " * ")) { define = MUL; }
    else if (!strcmp(str, " / ")) { define = DIV; }
    else if (!strcmp(str, " % ")) { define = MOD; }
    else if (!strcmp(str, " ^ ")) { define = SQR; }
    else if (!strcmp(str, " sqrt") || !strcmp(str, "sqrt")) { define = SQRT; }
    else if (!strcmp(str, " sin") || !strcmp(str, "sin")) { define = SIN; }
    else if (!strcmp(str, " cos") || !strcmp(str, "cos")) { define = COS; }
    else if (!strcmp(str, " asin") || !strcmp(str, "asin")) { define = ASIN; }
    else if (!strcmp(str, " acos") || !strcmp(str, "acos")) { define = ACOS; }
    else if (!strcmp(str, " tan") || !strcmp(str, "tan")) { define = TAN; }
    else if (!strcmp(str, " atan") || !strcmp(str, "atan")) { define = ATAN; }
    else if (!strcmp(str, " log") || !strcmp(str, "log")) { define = LOG; }
    else if (!strcmp(str, " ln") || !strcmp(str, "ln")) { define = LN; }
    else if (!strcmp(str, "(")) { define = BRACKET_LEFT; }
    else if (!strcmp(str, ")")) { define = BRACKET_RIGHT; }
    return define;
}

int priority(int oper, Node** nums) {
    int prior = 0;
    switch (oper) {
        case ')':
            prior = 0;
            break;
        case SUM:
        case SUB:
            prior = 1;
            break;
        case MUL:
        case DIV:
        case MOD:
            prior = 2;
            break;
        case SQR:
            prior = 3;
            break;
        case SQRT:
        case SIN:
        case COS:
        case ASIN:
        case ACOS:
        case TAN:
        case ATAN:
        case LOG:
        case LN:
            prior = 4;
            break;
        case UNAR_SUB:
            prior = 5;
            push(nums, 0);
            break;
        case '(':
            prior = 6;
            break;
    }
    return prior;
}

void operation(Node** nums, Node** opers) {
    long double x = 0, y = 0, res = 0;
    if ((*opers)->priority == 4) {
        x = pop(nums);
    } else {
        y = pop(nums);
        x = pop(nums);
    }
    switch ((int)pop(opers)) {
        case SUM:
            res = x + y;
            break;
        case SUB:
        case UNAR_SUB:
            res = x - y;
            break;
        case MUL:
            res = x * y;
            break;
        case DIV:
            res = x / y;
            break;
        case SQR:
            res = pow(x, y);
            break;
        case SQRT:
            res = sqrt(x);
            break;
        case SIN:
            res = sin(x);
            break;
        case COS:
            res = cos(x);
            break;
        case ASIN:
            res = asin(x);
            break;
        case ACOS:
            res = acos(x);
            break;
        case TAN:
            res = tan(x);
            break;
        case ATAN:
            res = atan(x);
            break;
        case LOG:
            res = log10(x);
            break;
        case LN:
            res = log(x);
            break;
    }
    push(nums, res);
}

void priority_compare(Node** nums, Node** opers, int current_oper_prior) {
    while ((*opers)->priority >= current_oper_prior) {
        if ((*opers)->priority == 6 && current_oper_prior == 0) {  //  '( )'
            pop(opers);
            if ((*opers)->priority == 4) {
                operation(nums, opers);
            }
            break;
        } else if ((*opers)->priority == 6 || ((*opers)->value == UNAR_SUB && current_oper_prior == 4)) {
            break;                                                  //   "(" not a ')' && -cos
        }
        operation(nums, opers);
    }
}

int brackets_check(const char* str, char* tmp) {
    if (((*(str - 1) == '(' || *(str - 1) == ')') && ((*tmp == '(' || *tmp == ')')))
     || (*str == '(' && *tmp != '\0') || (!strcmp(tmp, "-"))) {
        return 0;
     }
    return 1;
}

double parser(const char** str) { // Ne+10^6
    Node* nums_stack = (Node*)calloc(1, sizeof(Node));
    Node* oper_stack = (Node*)calloc(1, sizeof(Node));
    for (int i = 0; *str[0] != '\0'; i++) {
        if (is_num(str[0]) != NOT_A_NUM) {
            push(&nums_stack, atof_p(str));
        } else {
            char* str_oper = (char*)calloc(5, sizeof(char));
            int space_count = 0;
            for (int i = 0; is_num(str[0]) == NOT_A_NUM && space_count < 2; i++) {
                if (*str[0] == ' ') space_count++;
                if (brackets_check(str[0], str_oper) == 0) break;
                str_oper[i] = *str[0]++;
            }
            int* tmp_prior = (int*)calloc(1, sizeof(int));
            int* int_oper = (int*)calloc(1, sizeof(int));
            *int_oper = oper_define(str_oper);
            *tmp_prior = priority(*int_oper, &nums_stack);
            if ((oper_stack->priority >= *tmp_prior && oper_stack->value != BRACKET_LEFT) ||
                (oper_stack->value == BRACKET_LEFT && *int_oper == BRACKET_RIGHT)) {
                priority_compare(&nums_stack, &oper_stack, *tmp_prior);
            }
            if (str_oper[0] == ')') continue;
            push(&oper_stack, *int_oper);
            oper_stack->priority = *tmp_prior;
            free(int_oper);
            free(str_oper);
            free(tmp_prior);
        }
    }
    while (oper_stack->index != 0) {
        operation(&nums_stack, &oper_stack);
    }
    double result = nums_stack->value;
    free(nums_stack);
    free(oper_stack);
    return result;
}
