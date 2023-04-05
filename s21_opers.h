#ifndef S21_OPERS_H
#define S21_OPERS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stek_queue.h"
#define QTY_OF_OPERS 18

enum oper_type { NO_OPER_TYPE, BRACKETS, FUNC, SIMPLE, SEP };

struct stack_calc_opers {
  size_t count;
  struct calc_oper *data;
  size_t size;
};

// typedef maybe_num (*handler__kk)(struct stack_double *);

struct calc_oper {
  enum oper_category category;
  enum oper_type type;
  int32_t priority;
  size_t lenght;
  const char *name;
  size_t min_qty_opers;
};

// struct for_notation_oper {
//   enum oper_category category;
//   enum oper_type type;
//   int32_t priority;
//   size_t lenght;
//   const char *name;
// }

const struct calc_oper non_calc_oper();
typedef bool find(struct calc_oper, struct calc_oper);

struct stack_calc_opers stack_calc_opers_create(size_t sz);
bool stack_calc_opers_push(struct stack_calc_opers *s, struct calc_oper value);
struct calc_oper init(enum oper_category category, enum oper_type type,
                      int8_t priority, char *name, size_t min_qty_opers);
void stack_calc_opers_destroy(struct stack_calc_opers *s);
bool stack_calc_opers_full(const struct stack_calc_opers *s);

struct calc_oper stack_calc_opers_find(struct calc_oper cat,
                                       const struct stack_calc_opers *s,
                                       find f);

bool find_name(struct calc_oper needle, struct calc_oper haystack);
bool find_type(struct calc_oper needle, struct calc_oper haystack);
bool find_priority(struct calc_oper needle, struct calc_oper haystack);
bool find_category(struct calc_oper needle, struct calc_oper haystack);

enum oper_category operator_check(char const *str, char **end,
                                  const struct stack_calc_opers *s);

enum oper_type operator_type(enum oper_category cat,
                             const struct stack_calc_opers *s);
#endif  // S21_OPERS_H