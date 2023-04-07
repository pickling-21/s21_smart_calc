
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
      struct operator_info curr = check_operators(opers, &str);
      if (curr.o_type != O_NO_TYPE) add_operators(opers, &stack, l, curr);
    }
  }
  return head.next;
}

bool is_digit(char c) { return (c >= '0' && c <= '9'); }

void add_number(struct list *l, char const **str) {
  char *end_number = NULL;
  double number = strtod(*str, &end_number);
  list_add_back_num(&l, number);
  *str = end_number;
}

struct operator_info check_operators(struct stack_operators *opers,
                                     char const **str) {
  struct operator_info o = stack_operators_find_str(opers, *str);
  if (o.full_name != NULL) *str = *str + strlen(o.full_name);
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

// void add_opeators(struct stack_operators *s, struct list *l, struct opers
// o,
//                   const struct stack_calc_opers *opers) {
//   o.top = stack_c.opers_st.last(s);
//   if (o.curr.type == FUNC || o.curr.category == CAT_LEFT) {
//     // Функция или открывающая скобка - помещаем в стек.

//     stack_c.opers_st.push(s, o.curr);
//   } else if (o.curr.type == SEP) {
//     // Разделитель аргументов функции (например, запятая):
//     // Перекладываем операторы из стека в выходную очередь пока лексемой
//     на
//     // вершине стека не станет открывающая скобка. Если в стеке не
//     окажется
//     // открывающей скобки - в выражении допущена ошибка.

//     while (o.top.category != CAT_LEFT && o.top.category != CAT_NONE) {
//       last_from_stack_to_list(l, s);
//       o.top = stack_c.opers_st.last(s);
//     }
//     // if(o.top == NONE) - ERROR , так как в стэке должна быть
//     открывающаяся
//     // скобка
//   } else if (o.curr.type == SIMPLE) {
//     if (stack_c.opers_st.empty(s) || top_is_less_curr(o)) {
//       stack_c.opers_st.push(s, o.curr);
//     } else {
//       while (o.top.category != CAT_LEFT && !top_is_less_curr(o) &&
//              o.top.category != CAT_NONE) {
//         // выталкиваем из стека все операции, пока топ больше или равен
//         чем
//         // входящая. Или так: выталкиваем из стека пока не встретим в нем
//         // операцию, которая меньше входящей по приоритету ()
//         last_from_stack_to_list(l, s);
//         o.top = stack_c.opers_st.last(s);
//       }
//       stack_c.opers_st.push(s, o.curr);
//     }
//   } else if (o.curr.category == CAT_RIGHT) {
//     while (o.top.category != CAT_LEFT && o.top.category != CAT_NONE) {
//       last_from_stack_to_list(l, s);
//       o.top = stack_c.opers_st.last(s);
//     }
//     if (o.top.category == CAT_LEFT) stack_c.opers_st.pop(s);

//     if (o.top.type) {
//       last_from_stack_to_list(l, s);
//       // Если стек закончился до того, как была встречена открывающая
//       скобка - в
//       // выражении содержится ошибка.
//     }
//   }
// }

// struct list *inf_to_post(char const *str,
//                          const struct stack_calc_opers *opers) {
//   struct list head = {0};
//   struct list *l = &head;
//   struct stack_operators stack = stack_c.opers_st.create(OPERS_SIZE);
//   struct stack_operators *s = &stack;
//   int i = 0;
//   char const *tmp = str;
//   while (*tmp != '\0') {
//     if (is_digit(*tmp)) {
//       add_number(l, &tmp);
//     } else {
//       struct opers o = {none_oper_info(), none_oper_info()};
//       char *end_oper = NULL;
//       o.curr = operator_check(tmp, &end_oper, opers);
//       if (o.curr.category != CAT_NONE) {
//         add_opeators(s, l, o, opers);
//         tmp = end_oper;
//       } else {
//         tmp++;
//       }
//       printf("%d ", i);
//       i = i + 1;
//       stack_c.opers_st.print(s);
//       printf("\n");
//     }
//   }
//   for (bool res = true; res;) res = last_from_stack_to_list(l, s);
//   stack_c.opers_st.destroy(s);
//   return head.next;
// }

// bool top_is_less_curr(const struct opers o) {
//   return o.top.priority < o.curr.priority;
// }

// enum oper_type operator_type(enum oper_type);
