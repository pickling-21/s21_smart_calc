#ifndef S21_CALC_H
#define S21_CALC_H
#include "stack/s21_operators.h"

enum va_error {
  VA_OK,
  VA_BRACKETS,
  VA_MALLOC_RES,
  VA_NO_OPER,
  VA_OPERS_IN_ROW,
};

void print_error(enum va_error err);
void s21_calc(struct stack_operators* s);

#endif  // S21_CALC_H
