#include <stdlib.h>
#include <string.h>

#include "../structs/s21_operators.h"
#include "s21_polish_format.h"

enum va_error validator(struct list* inf_expression) {
  enum va_error res = VA_OK;
  struct stack_ptr_operators brackets_stack = {0};
  struct stack_ptr_operators* br = &brackets_stack;
  bool operand = false;

  if (stack_ptr_operators_create(br, STACK_BRACKETS_SIZE)) {
    struct va_opers o = {.curr = NULL, .prev = NULL};
    for (size_t i = 0; res == VA_OK && inf_expression; i++) {
      if (inf_expression->value.type == L_NUMBER) {
        inf_expression = inf_expression->next;
        operand = true;
        continue;
      } else if (inf_expression->value.type == L_OPERATOR) {
        o.curr = inf_expression->value.oper;
        if (!check_opers(o, i, operand)) res = VA_OPERS_IN_ROW;
        if (res == VA_OK) {
          res = brackets_okey(br, o.curr);
          inf_expression = inf_expression->next;
          operand = false;
        }
      } else {
        res = VA_NO_OPER;
      }
      o.prev = o.curr;
      if (operand == true) operand = false;
    }
    if (!stack_ptr_operators_is_empty(br)) res = VA_BRACKETS;
    stack_ptr_operators_destroy(br);
  } else
    res = MEM_MALLOC_RES;
  return res;
}

bool check_opers(struct va_opers o, size_t i, bool prev_operand) {
  bool res = true;
  (void)prev_operand;
  if (o.curr) {
    if (o.curr->o_type == O_BINARY && i == 0) res = false;
    // если бинарный в начале строки
    if (o.curr->o_type == O_BINARY && o.prev && o.prev->o_type == O_BINARY &&
        !prev_operand)
      res = false;
    // если два бинарных подряд
    if (o.prev && o.prev->o_type == O_UNARY && o.curr->o_type == O_UNARY &&
        is_left_assoc(o.prev) && is_left_assoc(o.curr) && !prev_operand)
      res = false;
    // унарные
  }
  return res;
}

enum va_error brackets_okey(struct stack_ptr_operators* br,
                            struct operator_info* o) {
  enum va_error res = VA_OK;
  if (is_open_bracket(o)) {
    if (!stack_ptr_operators_push(br, o)) res = MEM_REALLOC_RES;
  }
  if (is_close_bracket(o)) {
    if (stack_ptr_operators_is_empty(br)) {
      res = VA_BRACKETS;
    } else {
      stack_ptr_operators_pop(br);
    }
  }
  return res;
}
