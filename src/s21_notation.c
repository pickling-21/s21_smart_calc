
#include "s21_notation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack/s21_list.h"
#include "stack/s21_operators.h"

struct list *inf_to_post(char const *str, struct stack_operators *opers) {
  struct list head = {0};
  struct list *l = &head;
  struct stack_operators stack = stack_operators_create(STACK_SIZE);
  while (*str != '\0') {
    if (is_digit(*str)) {
      add_number(l, &str);
    } else {
      struct operator_info curr = check_operators_nat_name(opers, &str);
      if (curr.o_type != O_NO_TYPE) add_operators(opers, &stack, l, curr);
    }
  }
  return head.next;
}

static bool is_digit(char c) { return (c >= '0' && c <= '9'); }

void add_number(struct list *l, char const **str) {
  char *end_number = NULL;
  double number = strtod(*str, &end_number);
  list_add_back_num(&l, number);
  *str = end_number;
}

struct operator_info check_operators_nat_name(struct stack_operators *opers,
                                              char const **str) {
  struct operator_info o = stack_operators_find_nat_name(opers, *str);
  if (o.full_name != NULL) *str = *str + strlen(o.full_name);
  return o;
}

bool is_operation(struct operator_info o) {
  return o.o_type == O_BINARY || o.o_type == O_UNARY;
}

bool is_open_bracket(struct operator_info o) {
  return o.o_type == O_LEFT_BRACKET;
}

bool is_close_bracket(struct operator_info o) {
  return o.o_type == O_RIGHT_BRACKET;
}

void add_operators(struct stack_operators *opers, struct stack_operators *s,
                   struct list *l, struct operator_info curr) {
  struct operators o = {.curr = curr, .top = stack_operators_last(s)};
  if (stack_operators_is_empty(s) || is_open_bracket(o.curr)) {
    // если стак пустой или скобка открытая
    stack_operators_push(s, o.curr);
  } else if (is_operation(o.curr)) {
    // если операция
    if (o.top.priority >= o.curr.priority) {
      while (o.top.priority >= o.curr.priority) {
        last_from_stack_to_list(l, s);
        o.top = stack_operators_last(s);
      }
      stack_operators_push(s, o.curr);
    }
  } else if (is_close_bracket(o.curr)) {
    while (!is_open_bracket(o.top)) {
      last_from_stack_to_list(l, s);
      o.top = stack_operators_last(s);
    }
    stack_operators_pop(s);
  }
}