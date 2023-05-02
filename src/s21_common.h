#ifndef S21_COMMON_H
#define S21_COMMON_H
#include <stdbool.h>

#include "structs/s21_operators.h"
enum va_error {
  VA_OK,
  VA_BRACKETS,
  VA_MALLOC_RES,
  VA_NO_OPER,
  VA_OPERS_IN_ROW,
};

struct maybe_num {
  double value;
  bool valid;
};

struct maybe_num none_num();
struct maybe_num some_num(double i);
void print_error(enum va_error err);
bool is_operation(struct operator_info o);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

bool is_operand(char c);
#endif  // S21_COMMON_H