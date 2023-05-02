#ifndef S21_POLISH_FORMAT_H
#define S21_POLISH_FORMAT_H
#include <stdbool.h>
#include <stdio.h>

#include "../s21_calc.h"
#include "../s21_common.h"
#include "../structs/s21_list.h"
#include "../structs/s21_operators.h"

#define STACK_SIZE 300
#define STACK_BRACKETS_SIZE 200

struct va_opers {
  struct operator_info curr;
  struct operator_info prev;
};

struct nat_opers {
  struct operator_info curr;
  struct operator_info top;
};

/*=========*/
// polish format
enum va_error polish_format(struct stack_operators *s,
                            struct list **polish_expression, char *expression);

/*=========*/
// valid
bool check_opers(struct va_opers o, size_t i);
bool unary_or_binanry_two(struct operator_info curr, struct operator_info next);
struct operator_info unary_from_two(struct operator_info curr,
                                    struct operator_info next);
struct operator_info binary_from_two(struct operator_info curr,
                                     struct operator_info next);

enum va_error validator(const char *str, const struct stack_operators *opers);

bool brackets_okey(struct stack_operators *br, struct operator_info o);

/*=========*/
// replace
bool is_space(const char sym);
enum va_error replace_full_name(const struct stack_operators *opers,
                                const char *str, char *result);
void replace_one(const struct operator_info o, bool *may_unary);
void replace_and_write(const char **str, char **res, char *full, char *nat);
void replace_unary_clones(const struct stack_operators *fr, bool *may_unary,
                          const size_t curr, char **nat_name);

/*=========*/
// from inf to post
struct list *inf_to_post(char const *str, struct stack_operators *opers);

void add_operators(struct stack_operators *opers, struct stack_operators *s,
                   struct list *l, struct operator_info curr);

void add_number(struct list *l, char const **str);
struct operator_info check_operators_nat_name(struct stack_operators *opers,
                                              char const **str);

void add_operators(struct stack_operators *opers, struct stack_operators *s,
                   struct list *l, struct operator_info curr);
bool is_left_assoc(struct operator_info curr);

#endif  // S21_POLISH_FORMAT_H