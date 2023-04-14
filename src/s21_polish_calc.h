#ifndef S21_POLISH_CALC_H
#define S21_POLISH_CALC_H
#define STACK_DOUBLE_SIZE 300
#include "stack/s21_list.h"

enum va_error polish_calc(const struct stack_operators *opers,
                          struct list *polish_expression, double *result);
#endif  // S21_POLISH_CALC_H
