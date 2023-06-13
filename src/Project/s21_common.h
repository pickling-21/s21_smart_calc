#ifndef S21_COMMON_H
#define S21_COMMON_H
#include <stdbool.h>

#include "structs/s21_operators.h"
enum va_error {
  VA_OK = 0,
  CALC_ERROR_NUM_INF = 1,
  CALC_ERROR_NUM_NAN = 2,
  VA_ERROR_NUM = 3,
  VA_BRACKETS = 4,
  VA_NO_OPER = 5,
  VA_OPERS_IN_ROW = 6,
  CALC_STACK_UNDERFLOW = 7,
  CALC_ERROR = 8,
  MEM_MALLOC_RES_STR = 9,
  MEM_REALLOC_RES = 10,
  MEM_MALLOC_RES = 11,
};

void print_error(enum va_error err);
bool is_operation(struct operator_info* o);
bool is_open_bracket(struct operator_info* o);
bool is_close_bracket(struct operator_info* o);
bool is_left_assoc(struct operator_info* curr);
bool is_operand(char c);

#endif  // S21_COMMON_H