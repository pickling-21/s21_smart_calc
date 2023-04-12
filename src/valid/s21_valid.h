#ifndef S21_VALID_H
#define S21_VALID_H
#include <stdbool.h>
#include <stdio.h>

#include "../s21_calc.h"
#include "../s21_common.h"
#include "../stack/s21_operators.h"

struct str_info {
  char* str;
  size_t len;
};

struct va_opers {
  struct operator_info curr;
  struct operator_info prev;
};

bool is_space(const char sym);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

bool check_opers(struct va_opers o, size_t i);
bool unary_or_binanry_two(struct operator_info curr, struct operator_info next);
struct operator_info unary_from_two(struct operator_info curr,
                                    struct operator_info next);
struct operator_info binary_from_two(struct operator_info curr,
                                     struct operator_info next);

enum va_error validator(const char* str, const struct stack_operators* opers);

bool brackets_okey(struct stack_operators* br, struct operator_info o);

/*=========*/
// replace
enum va_error replace_full_name(const struct stack_operators* opers,
                                const char* str, char* result);
void replace_one(const struct operator_info o, bool* may_unary);
void replace_and_write(const char** str, char** res, char* full, char* nat);
void replace_unary_clones(const struct stack_operators* fr, bool* may_unary,
                          const size_t curr, char* nat_name);

#endif  // S21_VALID_H