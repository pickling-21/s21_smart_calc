
#include "s21_notation.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_notation.h"
#include "s21_opers.h"
#include "s21_stek_queue.h"

const struct stack_interface stack_c = {
    .opers_st = {stack_operators_create, stack_operators_is_empty,
                 stack_operators_is_full, stack_operators_destroy,
                 stack_operators_push, stack_operators_pop,
                 stack_operators_last, stack_operators_print}};

struct list *inf_to_post(char const *str,
                         const struct stack_calc_opers *opers) {
  struct list head = {0};
  struct list *l = &head;
  struct stack_operators stack = stack_c.opers_st.create(OPERS_SIZE);
  struct stack_operators *s = &stack;
  int i = 0;
  char const *tmp = str;
  while (*tmp != '\0') {
    if (is_digit(*tmp)) {
      add_number(l, &tmp);
    } else {
      struct opers o = {CAT_NONE, CAT_NONE};
      char *end_oper = NULL;
      o.curr = operator_check(tmp, &end_oper, opers);
      if (o.curr != CAT_NONE) {
        add_opeators(s, l, o, opers);
        tmp = end_oper;
      } else {
        tmp++;
      }
      printf("%d ", i);
      i = i + 1;
      stack_c.opers_st.print(s);
      printf("\n");
    }
  }
  for (bool res = true; res;) res = last_from_stack_to_list(l, s);
  stack_c.opers_st.destroy(s);
  return head.next;
}

bool top_is_less_curr(const struct opers o,
                      const struct stack_calc_opers *opers) {
  struct calc_oper curr = non_calc_oper();
  curr.category = o.curr;
  struct calc_oper top = non_calc_oper();
  top.category = o.top;
  int32_t p_top = stack_calc_opers_find(top, opers, find_priority).priority;
  int32_t p_curr = stack_calc_opers_find(curr, opers, find_priority).priority;
  return p_top < p_curr;
}

bool is_digit(char c) { return (c >= '0' && c <= '9'); }

void add_number(struct list *l, char const **str) {
  char *end_number = NULL;
  double number = strtod(*str, &end_number);
  struct symbols n = some_number(number);
  list_add_back(&l, n);
  *str = end_number;
}

void add_opeators(struct stack_operators *s, struct list *l, struct opers o,
                  const struct stack_calc_opers *opers) {
  enum oper_type curr_type = operator_type(o.curr, opers);
  o.top = stack_c.opers_st.last(s);

  if (curr_type == FUNC || o.curr == CAT_LEFT) {
    // Функция или открывающая скобка - помещаем в стек.

    stack_c.opers_st.push(s, o.curr);
  } else if (curr_type == SEP) {
    // Разделитель аргументов функции (например, запятая):
    // Перекладываем операторы из стека в выходную очередь пока лексемой на
    // вершине стека не станет открывающая скобка. Если в стеке не окажется
    // открывающей скобки - в выражении допущена ошибка.

    while (o.top != CAT_LEFT && o.top != CAT_NONE) {
      last_from_stack_to_list(l, s);
      o.top = stack_c.opers_st.last(s);
    }
    // if(o.top == NONE) - ERROR , так как в стэке должна быть открывающаяся
    // скобка
  } else if (curr_type == SIMPLE) {
    if (stack_c.opers_st.empty(s) || top_is_less_curr(o, opers)) {
      stack_c.opers_st.push(s, o.curr);
    } else {
      while (o.top != CAT_LEFT && !top_is_less_curr(o, opers) &&
             o.top != CAT_NONE) {
        // выталкиваем из стека все операции, пока топ больше или равен чем
        // входящая. Или так: выталкиваем из стека пока не встретим в нем
        // операцию, которая меньше входящей по приоритету ()
        last_from_stack_to_list(l, s);
        o.top = stack_c.opers_st.last(s);
      }
      stack_c.opers_st.push(s, o.curr);
    }
  } else if (o.curr == CAT_RIGHT) {
    while (o.top != CAT_LEFT && o.top != CAT_NONE) {
      last_from_stack_to_list(l, s);
      o.top = stack_c.opers_st.last(s);
    }
    if (o.top == CAT_LEFT) stack_c.opers_st.pop(s);

    if (operator_type(o.top, opers) == FUNC) {
      last_from_stack_to_list(l, s);
      // Если стек закончился до того, как была встречена открывающая скобка - в
      // выражении содержится ошибка.
    }
  }
}
