#ifndef S21_COMMON_H
#define S21_COMMON_H
#include <stdbool.h>
#define X 3.141593
#include "structs/s21_operators.h"
enum va_error {
  VA_OK,
  VA_BRACKETS,
  VA_MALLOC_RES,
  VA_NO_OPER,
  VA_OPERS_IN_ROW,
  VA_STACK_UNDERFLOW,
  VA_ERROR_NUM,
  VA_ERROR_CALC
};

void print_error(enum va_error err);
bool is_operation(struct operator_info o);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

bool is_operand(char c);

#endif  // S21_COMMON_H