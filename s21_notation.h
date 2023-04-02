#ifndef S21_NOTATION_H
#define S21_NOTATION_H
#include <stdbool.h>

#include "s21_stek_queue.h"
#define OPERS_SIZE 1000

#define QTY_OF_OPERS 18

struct opers {
  enum oper_category curr;
  enum oper_category top;
};

enum oper_type {
  NO_OPER_TYPE,
  BRACKETS,
  FUNC,
  SIMPLE,
};

struct oper {
  enum oper_category category;
  enum oper_type type;
  int8_t priority;
  size_t lenght;
  char *str;
};

struct list *inf_to_post();

bool is_digit(char c);
enum oper_category operator_check(char const *str, char **end);

void add_number(struct list *l, char **str);
void add_opeators(struct stack_operators *s, struct list *l, struct opers o);

bool top_is_less_curr(struct opers o);
enum oper_category convert_one_sym_to_enum(const char c);
enum oper_category convert_three_sym_to_enum(const char *str);
enum oper_category operator_check(char const *str, char **end);
#endif  // S21_NOTATION_H