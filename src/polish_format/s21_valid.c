#include <stdlib.h>
#include <string.h>

#include "../structs/s21_operators.h"
#include "s21_polish_format.h"

enum va_error validator(const char* str, const struct stack_operators* opers) {
  enum va_error res = VA_OK;
  struct stack_operators brackets_stack =
      stack_operators_create(STACK_BRACKETS_SIZE);
  struct stack_operators* br = &brackets_stack;
  struct va_opers o = {.curr = none_operator(), .prev = none_operator()};
  for (size_t i = 0; *str != '\0' && res == VA_OK; i++) {
    if (is_operand(*str)) {
      str++;
      o.prev.o_type = O_NO_TYPE;
      continue;
    }
    o.curr = stack_operators_find_nat_name(opers, str);

    if (!brackets_okey(br, o.curr)) res = VA_BRACKETS;

    if (!check_opers(o, i)) {
      res = VA_OPERS_IN_ROW;
    }
    str += strlen(o.curr.nat_name);
    o.prev = stack_operators_copy(o.curr);
    stack_operators_free_names(o.curr);
  }
  if (o.prev.o_type != O_NO_TYPE) stack_operators_free_names(o.prev);
  if (!stack_operators_is_empty(br)) res = VA_BRACKETS;
  stack_operators_destroy(br);
  printf("\n----------\nVALID END\n");
  return res;
}

bool check_opers(struct va_opers o, size_t i) {
  bool res = true;
  if (o.curr.o_type == O_BINARY && i == 0) res = false;
  if (o.curr.o_type == O_BINARY && o.prev.o_type == O_BINARY) res = false;
  if (o.prev.o_type == O_UNARY && o.curr.o_type == O_BINARY) res = false;
  return res;
}

bool brackets_okey(struct stack_operators* br, struct operator_info o) {
  bool res = true;
  if (is_open_bracket(o)) stack_operators_push(br, o);
  if (is_close_bracket(o)) {
    if (stack_operators_is_empty(br)) {
      res = false;
    } else {
      stack_operators_pop(br);
    }
  }
  return res;
}
