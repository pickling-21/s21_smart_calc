#ifndef S21_VALID_H
#define S21_VALID_H
#include <stdbool.h>
#include <stdio.h>

#include "stack/s21_operators.h"

enum valid_erorrs {
  VA_OK,
  VA_BRACKETS,
  VA_MALLOC_RES,
};

struct str_info {
  char* str;
  size_t len;
};

bool is_space(const char sym);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

enum valid_erorrs validator(const char* str, char* res_str,
                            const struct stack_operators* opers);

void remove_spaces(const char* str, char* result);

void replace_full_name(const struct stack_operators* opers,
                       struct str_info* res);

struct operator_info find_one(struct stack_operators* s, char const* str);

struct operator_info check_operators_full_name(
    const struct stack_operators* opers, char const* str);
// void replace_unary_minus(char* str, const struct
// stack_operators* opers);
// bool brackets_okey(const char* str, const struct stack_operators* opers);

void print_error(enum valid_erorrs err);

#endif  // S21_VALID_H