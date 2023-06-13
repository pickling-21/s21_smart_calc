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
  struct operator_info *curr;
  struct operator_info *prev;
};

struct nat_opers {
  struct operator_info *curr;
  struct operator_info *top;
};

/*=========*/
// polish format
void remove_unnecessary(const char *expression, char *result);
enum va_error polish_format(const struct stack_operators *opers,
                            struct list **polish_expression,
                            const char *expression, double x);

/*=========*/
// valid
bool check_opers(struct va_opers o, size_t i, bool prev_operand);
enum va_error validator(struct list *inf_expression);

enum va_error brackets_okey(struct stack_ptr_operators *br,
                            struct operator_info *o);

/*=========*/
// replace
bool is_space(const char sym);

enum va_error find_and_add_operation_to_list(
    const struct stack_operators *opers, const char **str,
    struct list **list_res, bool *may_unary);

enum va_error replace_full_name(const struct stack_operators *opers,
                                const char *str, struct list **list_res,
                                double x);

void replace_one(const struct operator_info *o, bool *may_unary);

void replace_unary_clones(const struct stack_ptr_operators *fr, bool *may_unary,
                          struct operator_info **finded);

bool unary_or_binanry_two(struct operator_info *curr,
                          struct operator_info *next);
struct operator_info *unary_from_two(struct operator_info *curr,
                                     struct operator_info *next);
struct operator_info *binary_from_two(struct operator_info *curr,
                                      struct operator_info *next);

/*=========*/
// from inf to post
enum va_error inf_to_post(struct list *inf_expression,
                          struct list **polish_expression);

bool add_operators(struct stack_ptr_operators *s, struct list *l,
                   struct operator_info *curr);
bool add_number(struct list **l, char const **str, double x);

#endif  // S21_POLISH_FORMAT_H