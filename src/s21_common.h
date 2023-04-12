#ifndef S21_COMMON_H
#define S21_COMMON_H
#include <stdbool.h>

#include "stack/s21_operators.h"
bool is_operation(struct operator_info o);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

bool is_operand(char c);
#endif  // S21_COMMON_H