
#include "s21_notation.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stek_queue.h"

const struct oper opers[QTY_OF_OPERS] = {
    [NONE] = {.category = NONE,
              .lenght = 0,
              .priority = 0,
              .type = NO_OPER_TYPE,
              .str = NULL},
    [SIN] = {.category = SIN,
             .type = FUNC,
             .priority = 0,
             .lenght = 3,
             .str = "sin"},
    [COS] = {.category = COS,
             .type = FUNC,
             .priority = 0,
             .lenght = 3,
             .str = "cos"},
    [LEFT] = {.category = LEFT,
              .lenght = 1,
              .priority = 0,
              .str = "(",
              .type = BRACKETS},
    [RIGHT] = {.category = RIGHT,
               .lenght = 1,
               .priority = 0,
               .str = ")",
               .type = BRACKETS},
    [PLUS] = {.category = PLUS,
              .lenght = 1,
              .priority = 1,
              .str = "+",
              .type = SIMPLE},
    [MINUS] = {.category = MINUS,
               .lenght = 1,
               .priority = 1,
               .str = "-",
               .type = SIMPLE},
    [MUL] = {.category = MUL,
             .lenght = 1,
             .priority = 2,
             .str = "*",
             .type = SIMPLE},
    [MOD] = {.category = MOD,
             .type = SIMPLE,
             .priority = 2,
             .lenght = 3,
             .str = "mod"},
    [DIV] = {.category = DIV,
             .type = SIMPLE,
             .priority = 2,
             .lenght = 1,
             .str = "/"},
    [POWER] = {.category = POWER,
               .type = SIMPLE,
               .priority = 3,
               .lenght = 1,
               .str = "^"},

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
      struct opers o = {NONE, NONE};
      char *end_oper = NULL;
      o.curr = operator_check(tmp, &end_oper);
      if (o.curr != NONE) {
        add_opeators(s, l, o);
        tmp = end_oper;
      } else {
        tmp++;
      }
    }
    printf("%d ", i);
    i = i + 1;
    stack_c.opers_st.print(s);
    printf("\n");
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
  enum oper_category result = NONE;
  *end = (char *)str;
  for (size_t i = 0, stop = 0; i < QTY_OF_OPERS && stop != 1; i++) {
    if (opers[i].str != NULL) {
      if (strncmp(str, opers[i].str, opers[i].lenght) == 0) {
        result = i;
        stop = 1;
      }
    }
  }
  *end += opers[result].lenght;
  return result;
}

void add_opeators(struct stack_operators *s, struct list *l, struct opers o) {
  o.top = stack_c.opers_st.last(s);
  if (opers[o.curr].type != BRACKETS) {
    if (stack_c.opers_st.empty(s) || o.top == LEFT) {
      stack_c.opers_st.push(s, o.curr);
    } else if (top_is_less_curr(o)) {
      stack_c.opers_st.push(s, o.curr);
    } else if (opers[o.curr].type == FUNC) {
      stack_c.opers_st.push(s, o.curr);
    } else {
      while (o.top != LEFT && !top_is_less_curr(o) && o.top != NONE) {
        // выталкиваем из стека все операции, пока топ больше или равен чем
        // входящая. Или так: выталкиваем из стека пока не встретим в нем
        // операцию, которая меньше входящей по приоритету ()
        last_from_stack_to_list(l, s);
        o.top = stack_c.opers_st.last(s);
      }
      stack_c.opers_st.push(s, o.curr);
    }
  } else if (opers[o.curr].type == BRACKETS) {
    if (o.curr == LEFT) {
      stack_c.opers_st.push(s, o.curr);
    } else if (o.curr == RIGHT) {
      while (o.top != LEFT && o.top != NONE) {
        last_from_stack_to_list(l, s);
        o.top = stack_c.opers_st.last(s);
      }
      if (o.top == LEFT) stack_c.opers_st.pop(s);
    }
  }
}
