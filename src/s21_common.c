#include "s21_common.h"

bool is_operation(struct operator_info o) {
  return o.o_type == O_BINARY || o.o_type == O_UNARY;
}

bool is_open_bracket(struct operator_info o) {
  return o.o_type == O_LEFT_BRACKET;
}

bool is_close_bracket(struct operator_info o) {
  return o.o_type == O_RIGHT_BRACKET;
}

bool is_operand(char c) {
  return (c >= '0' && c <= '9') || c == '.' || c == 'x';
}
