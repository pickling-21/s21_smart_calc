
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_common.h"
#include "../structs/s21_list.h"
#include "../structs/s21_operators.h"
#include "s21_polish_format.h"

struct list *inf_to_post(char const *str, struct stack_operators *opers) {
  printf("-------------------------------\n");
  printf("INF_TO_POST\n");
  printf("coming %s\n", str);
  struct list head = {0};
  struct list *l = &head;
  struct stack_operators stack = stack_operators_create(STACK_SIZE);
  int deli = 0;
  while (*str != '\0') {
    if (is_operand(*str)) {
      add_number(l, &str);
    } else {
      struct operator_info curr = check_operators_nat_name(opers, &str);
      if (curr.o_type != O_NO_TYPE) add_operators(opers, &stack, l, curr);
    }
    printf("%d ", deli);
    stack_operators_print(&stack);
    printf("\n");
    printf("%d list =", deli);
    printf("\n");
    deli++;

    list_print(l);
  }
  printf("\n\n");
  while (!stack_operators_is_empty(&stack)) {
    last_from_stack_to_list(l, &stack);
  }
  return head.next;
}

void add_number(struct list *l, char const **str) {
  char *end_number = NULL;
  if (**str != 'x') {
    double number = strtod(*str, &end_number);
    list_add_back_num(&l, number);
  } else {
    list_add_back_x(&l);
  }
  *str = (end_number != NULL) ? end_number : *str + 1;
}

struct operator_info check_operators_nat_name(struct stack_operators *opers,
                                              char const **str) {
  struct operator_info o = stack_operators_find_nat_name(opers, *str);
  if (o.full_name != NULL) *str = *str + strlen(o.nat_name);
  return o;
}

void add_operators(struct stack_operators *opers, struct stack_operators *s,
                   struct list *l, struct operator_info curr) {
  struct nat_opers o = {.curr = curr, .top = stack_operators_last(s)};
  if (stack_operators_is_empty(s) || is_open_bracket(o.curr)) {
    // если стак пустой или скобка открытая
    stack_operators_push(s, o.curr);
  } else if (is_operation(o.curr)) {
    // если операция
    while (!stack_operators_is_empty(s) &&
           ((is_left_assoc(o.curr) && o.top.priority >= o.curr.priority) ||
            (!is_left_assoc(o.curr) && o.top.priority > o.curr.priority))) {
      last_from_stack_to_list(l, s);
      o.top = stack_operators_last(s);
    }
    stack_operators_push(s, o.curr);
  } else if (is_close_bracket(o.curr)) {
    while (!is_open_bracket(o.top)) {
      last_from_stack_to_list(l, s);
      o.top = stack_operators_last(s);
    }
    stack_operators_pop(s);
  }
}

bool is_left_assoc(struct operator_info curr) {
  return curr.o_type == O_BINARY;
}