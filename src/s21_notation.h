#ifndef S21_NOTATION_H
#define S21_NOTATION_H
#include <stdbool.h>

#include "stack/s21_list.h"
#include "stack/s21_operators.h"
struct list *inf_to_post(char const *str, struct stack_operators *opers);
#define STACK_SIZE 300

// #define QTY_OF_OPERS 18

struct operators {
  struct operator_info curr;
  struct operator_info top;
};

void add_operators(struct stack_operators *opers, struct stack_operators *s,
                   struct list *l, struct operator_info curr);

struct list *inf_to_post(char const *str, struct stack_operators *opers);

bool is_digit(char c);
void add_number(struct list *l, char const **str);
struct operator_info check_operators_nat_name(struct stack_operators *opers,
                                              char const **str);
bool is_operation(struct operator_info o);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

void add_operators(struct stack_operators *opers, struct stack_operators *s,
                   struct list *l, struct operator_info curr);
// bool priority_top_is_less_curr(const struct opers o)

// void add_number(struct list *l, const char **str);

// bool top_is_less_curr(const struct opers o);
// struct read_notation operator_check(char const *str, char **end,
//                                     const struct stack_calc_opers *s);
#endif  // S21_NOTATION_H