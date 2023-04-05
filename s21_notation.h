#ifndef S21_NOTATION_H
#define S21_NOTATION_H
#include <stdbool.h>

#include "s21_opers.h"
#include "s21_stek_queue.h"

#define OPERS_SIZE 1000

#define QTY_OF_OPERS 18

struct opers {
  enum oper_category curr;
  enum oper_category top;
};

struct list *inf_to_post(char const *str, const struct stack_calc_opers *opers);

bool is_digit(char c);

void add_number(struct list *l, const char **str);

bool top_is_less_curr(const struct opers o,
                      const struct stack_calc_opers *opers);
void add_opeators(struct stack_operators *s, struct list *l, struct opers o,
                  const struct stack_calc_opers *opers);
#endif  // S21_NOTATION_H