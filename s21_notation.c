
#include "s21_notation.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stek_queue.h"

const struct oper opers[QTY_OF_OPERS] = {
    [CAT_NONE] = {.category = CAT_NONE,
                  .lenght = 0,
                  .priority = 0,
                  .type = NO_OPER_TYPE,
                  .str = NULL},
    [CAT_SIN] = {.category = CAT_SIN,
                 .type = FUNC,
                 .priority = 0,
                 .lenght = 3,
                 .str = "sin"},
    [CAT_COS] = {.category = CAT_COS,
                 .type = FUNC,
                 .priority = 0,
                 .lenght = 3,
                 .str = "cos"},
    [CAT_LEFT] = {.category = CAT_LEFT,
                  .lenght = 1,
                  .priority = 0,
                  .str = "(",
                  .type = BRACKETS},
    [CAT_RIGHT] = {.category = CAT_RIGHT,
                   .lenght = 1,
                   .priority = 0,
                   .str = ")",
                   .type = BRACKETS},
    [CAT_PLUS] = {.category = CAT_PLUS,
                  .lenght = 1,
                  .priority = 1,
                  .str = "+",
                  .type = SIMPLE},
    [CAT_MINUS] = {.category = CAT_MINUS,
                   .lenght = 1,
                   .priority = 1,
                   .str = "-",
                   .type = SIMPLE},
    [CAT_MUL] = {.category = CAT_MUL,
                 .lenght = 1,
                 .priority = 2,
                 .str = "*",
                 .type = SIMPLE},
    [CAT_MOD] = {.category = CAT_MOD,
                 .type = SIMPLE,
                 .priority = 2,
                 .lenght = 3,
                 .str = "mod"},
    [CAT_DIV] = {.category = CAT_DIV,
                 .type = SIMPLE,
                 .priority = 2,
                 .lenght = 1,
                 .str = "/"},
    [CAT_POWER] = {.category = CAT_POWER,
                   .type = SIMPLE,
                   .priority = 3,
                   .lenght = 1,
                   .str = "^"},
    [CAT_COMMA] = {.category = CAT_COMMA,
                   .type = SEP,
                   .priority = 0,
                   .lenght = 1,
                   .str = ","},

};

const struct stack_interface stack_c = {
    .opers_st = {stack_operators_create, stack_operators_is_empty,
                 stack_operators_is_full, stack_operators_destroy,
                 stack_operators_push, stack_operators_pop,
                 stack_operators_last, stack_operators_print}};

struct list *inf_to_post() {
  struct list head = {0};
  struct list *l = &head;
  enum oper_category *data = calloc(OPERS_SIZE, sizeof(enum oper_category));
  struct stack_operators stack = {.count = 0, .data = data, .size = OPERS_SIZE};
  struct stack_operators *s = &stack;
  char *str = "6+3*(1+4*5)*2";
  char *tmp = str;
  int i = 0;
  // char sign = 0;
  while (*tmp != '\0') {
    if (is_digit(*tmp)) {
      add_number(l, &tmp);
    } else {
      struct opers o = {CAT_NONE, CAT_NONE};
      char *end_oper = NULL;
      o.curr = operator_check(tmp, &end_oper);
      if (o.curr != CAT_NONE) {
        add_opeators(s, l, o);
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

bool top_is_less_curr(struct opers o) {
  return opers[o.top].priority < opers[o.curr].priority;
}

bool is_digit(char c) { return (c >= '0' && c <= '9'); }

void add_number(struct list *l, char **str) {
  char *end_number = NULL;
  double number = strtod(*str, &end_number);
  struct symbols n = some_number(number);
  list_add_back(&l, n);
  *str = end_number;
}

enum oper_category operator_check(char const *str, char **end) {
  printf("str oper check |%s|\n", str);
  enum oper_category result = CAT_NONE;
  *end = (char *)str;
  for (int i = 0; i < QTY_OF_OPERS && result == CAT_NONE; i++) {
    if (opers[i].str != NULL) {
      // printf("opers[ % d ].str = %s\n", i, opers[i].str);
      // printf("opers[ % d ].lenght = %ld\n", i, opers[i].lenght);
      if (strncmp(str, opers[i].str, opers[i].lenght) == 0) {
        // printf("operator checkAAAAA\n");
        result = i;
      }
    }
  }
  *end += opers[result].lenght;
  return result;
}

// void add_opeators(struct stack_operators *s, struct list *l, struct opers o)
// {
//   o.top = stack_c.opers_st.last(s);
//   if (opers[o.curr].type != BRACKETS) {
//     if (stack_c.opers_st.empty(s) || o.top == LEFT) {
//       stack_c.opers_st.push(s, o.curr);
//     } else if (top_is_less_curr(o)) {
//       stack_c.opers_st.push(s, o.curr);
//     } else if (opers[o.curr].type == FUNC) {
//       stack_c.opers_st.push(s, o.curr);
//     } else {
//       while (o.top != LEFT && !top_is_less_curr(o) && o.top != NONE) {
//         // выталкиваем из стека все операции, пока топ больше или равен чем
//         // входящая. Или так: выталкиваем из стека пока не встретим в нем
//         // операцию, которая меньше входящей по приоритету ()
//         last_from_stack_to_list(l, s);
//         o.top = stack_c.opers_st.last(s);
//       }
//       stack_c.opers_st.push(s, o.curr);
//     }
//   } else if (opers[o.curr].type == BRACKETS) {
//     if (o.curr == LEFT) {
//       stack_c.opers_st.push(s, o.curr);
//     } else if (o.curr == RIGHT) {
//       while (o.top != LEFT && o.top != NONE) {
//         last_from_stack_to_list(l, s);
//         o.top = stack_c.opers_st.last(s);
//       }
//       if (o.top == LEFT) stack_c.opers_st.pop(s);
//     }
//   }
// }

void add_opeators(struct stack_operators *s, struct list *l, struct opers o) {
  enum oper_type curr_type = opers[o.curr].type;
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
    if (top_is_less_curr(o)) {
      stack_c.opers_st.push(s, o.curr);
    } else {
      while (o.top != CAT_LEFT && !top_is_less_curr(o) && o.top != CAT_NONE) {
        // выталкиваем из стека все операции, пока топ больше или равен чем
        // входящая. Или так: выталкиваем из стека пока не встретим в нем
        // операцию, которая меньше входящей по приоритету ()
        last_from_stack_to_list(l, s);
        o.top = stack_c.opers_st.last(s);
      }
      stack_c.opers_st.push(s, o.curr);
    }
  } else if (o.curr == CAT_RIGHT) {
    printf("OOOOO\n\n");
    while (o.top != CAT_LEFT && o.top != CAT_NONE) {
      last_from_stack_to_list(l, s);
      o.top = stack_c.opers_st.last(s);
    }
    if (o.top == CAT_LEFT) stack_c.opers_st.pop(s);

    if (opers[o.top].type == FUNC) {
      last_from_stack_to_list(l, s);
      // Если стек закончился до того, как была встречена открывающая скобка - в
      // выражении содержится ошибка.
    }
  }
}
