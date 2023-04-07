#ifndef S21_VALID_H
#define S21_VALID_H
#include <stdbool.h>
#include <stdio.h>

#include "s21_opers.h"

enum valid_erorrs {
  VA_OK,
  VA_BRACKETS,
  VA_MALLOC_RES,
};

struct str_info {
  char* str;
  size_t len;
};

enum valid_erorrs validator(const char* str, char** res_str,
                            const struct stack_calc_opers* opers);

void remove_spaces(const char* str, char* result);
bool is_space(const char sym);

bool is_open_bracket(char s);
bool is_close_bracket(char s);
void replace_unary_minus(char* str);
bool brackets_okey(const char* str);

void print_error(enum valid_erorrs err);

#endif  // S21_VALID_H