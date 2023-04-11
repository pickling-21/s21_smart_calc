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

struct va_opers {
  struct operator_info curr;
  struct operator_info next;
};

static bool is_digit(char c);
bool is_space(const char sym);
bool is_open_bracket(struct operator_info o);
bool is_close_bracket(struct operator_info o);

bool check_opers(struct va_opers o, size_t i);
bool unary_or_binanry_two(struct operator_info curr, struct operator_info next);
struct operator_info unary_from_two(struct operator_info curr,
                                    struct operator_info next);
struct operator_info binary_from_two(struct operator_info curr,
                                     struct operator_info next);
void replace_and_write(const char** str, char** res, char* full, char* nat);

enum valid_erorrs validator(const char* str, char* res_str,
                            const struct stack_operators* opers);
void replace_full_name(const struct stack_operators* opers, const char* str,
                       char* result);
bool brackets_okey(struct stack_operators* br, struct operator_info o);
void print_error(enum valid_erorrs err);

#endif  // S21_VALID_H