
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_common.h"
#include "../structs/s21_list.h"
#include "../structs/s21_operators.h"
#include "s21_polish_format.h"

enum va_error inf_to_post(struct list *inf_expression,
                          struct list **polish_expression) {
  enum va_error err = VA_OK;
  struct stack_ptr_operators stack = {0};

  if (stack_ptr_operators_create(&stack, STACK_SIZE)) {
    for (; inf_expression && err == VA_OK;
         inf_expression = inf_expression->next) {
      if (inf_expression->value.type == L_NUMBER) {
        list_add_back(polish_expression, inf_expression->value);
      } else if (inf_expression->value.type == L_OPERATOR) {
        struct operator_info *curr = inf_expression->value.oper;
        if (curr != NULL)
          if (!add_operators(&stack, *polish_expression, curr))
            err = MEM_REALLOC_RES;
      }
    }

    while (!stack_ptr_operators_is_empty(&stack)) {
      last_from_stack_to_list(*polish_expression, &stack);
    }
    stack_ptr_operators_destroy(&stack);
  } else
    err = MEM_MALLOC_RES;

  return err;
}

bool add_operators(struct stack_ptr_operators *s, struct list *l,
                   struct operator_info *curr) {
  struct nat_opers o = {.curr = curr, .top = stack_ptr_operators_last(s)};
  bool res = true;
  if (stack_ptr_operators_is_empty(s) || is_open_bracket(o.curr)) {
    // если стак пустой или скобка открытая
    res = stack_ptr_operators_push(s, o.curr);
  } else if (is_operation(o.curr)) {
    // если операция
    while (!stack_ptr_operators_is_empty(s) &&
           ((is_left_assoc(o.curr) && o.top->priority >= o.curr->priority) ||
            (!is_left_assoc(o.curr) && o.top->priority > o.curr->priority))) {
      last_from_stack_to_list(l, s);
      o.top = stack_ptr_operators_last(s);
    }
    if (res == true) res = stack_ptr_operators_push(s, o.curr);
  } else if (is_close_bracket(o.curr)) {
    while (!is_open_bracket(o.top)) {
      last_from_stack_to_list(l, s);
      o.top = stack_ptr_operators_last(s);
    }
    stack_ptr_operators_pop(s);
  }
  return res;
}
