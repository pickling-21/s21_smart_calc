#ifndef S21_POLISH_CALC_H
#define S21_POLISH_CALC_H
#define STACK_DOUBLE_SIZE 300
#include "structs/s21_list.h"

enum va_error polish_calc(struct list *polish_expression, double *result);
#endif  // S21_POLISH_CALC_H
