#include <stdlib.h>
#include <string.h>

#include "../structs/s21_operators.h"
#include "s21_polish_format.h"

enum va_error validator(const char* str, const struct stack_operators* opers) {
  printf("----------\nVALID\n");

  enum va_error res = VA_OK;
  struct stack_operators brackets_stack =
      stack_operators_create(STACK_BRACKETS_SIZE);
  printf("1\n");
  struct stack_operators* br = &brackets_stack;
  printf("2\n");

  for (size_t curr = 0, prev = 0; str[curr] != '\0'; curr++, prev = curr) {
    printf("3\n");

    printf("curr = %ld\n", curr);
    if (is_operand(str[curr])) {
      continue;
    }

    struct va_opers o = {
        .curr = stack_operators_find_nat_name(opers, str + curr),
        .prev = none_operator()};
    if (prev != 0) o.prev = stack_operators_find_nat_name(opers, str + prev);

    res = (brackets_okey(br, o.curr) == false) ? VA_BRACKETS : VA_OK;
  }
  if (!stack_operators_is_empty(br)) res = VA_BRACKETS;
  stack_operators_destroy(br);
  printf("\n----------\nVALID END\n");
  return res;
}

bool check_opers(struct va_opers o, size_t i) {
  bool res = true;
  if (o.curr.o_type == O_BINARY && i == 0) res = false;
  if (o.curr.o_type == O_BINARY && o.prev.o_type == O_BINARY) res = false;
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
