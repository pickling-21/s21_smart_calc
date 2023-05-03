#include "s21_calc.h"

#include <math.h>
#include <stdio.h>

#include "polish_format/s21_polish_format.h"
#include "s21_polish_calc.h"
#include "structs/s21_double.h"
#include "structs/s21_list.h"
// 6+3*(1+4*5)*2
struct maybe_num s21_negate(double* s) { return some_num(-1 * s[0]); }
struct maybe_num s21_nothing(double* s) { return some_num(s[0]); }

struct maybe_num s21_sum(double* s) { return some_num(s[0] + s[1]); }
struct maybe_num s21_sub(double* s) { return some_num(s[0] - s[1]); }

struct maybe_num s21_mul(double* s) { return some_num(s[0] * s[1]); }
struct maybe_num s21_div(double* s) {
  return s[1] != 0 ? some_num(s[0] / s[1]) : nan_num();
}
struct maybe_num s21_mod(double* s) {
  return s[1] != 0 ? some_num(fmod(s[0], s[1])) : nan_num();
}

struct maybe_num s21_power(double* s) { return some_num(pow(s[0], s[1])); }

struct maybe_num s21_sin(double* s) { return some_num(sin(s[0])); }
struct maybe_num s21_cos(double* s) { return some_num(cos(s[0])); }
struct maybe_num s21_tan(double* s) { return some_num(tan(s[0])); }

int main() {
  struct stack_operators stack = stack_operators_create(QTY_OF_OPERS);
  struct stack_operators* s = &stack;
  stack_operators_push(s, some_operator("(", "(", O_LEFT_BRACKET, 0, NULL));
  stack_operators_push(s, some_operator(")", ")", O_RIGHT_BRACKET, 0, NULL));

  stack_operators_push(s, some_operator("+", "+", O_BINARY, 1, s21_sum));
  stack_operators_push(s, some_operator("+", "#", O_UNARY, 6, s21_negate));
  stack_operators_push(s, some_operator("-", "-", O_BINARY, 1, s21_sub));
  stack_operators_push(s, some_operator("-", "~", O_UNARY, 6, s21_nothing));

  stack_operators_push(s, some_operator("*", "*", O_BINARY, 2, s21_mul));
  stack_operators_push(s, some_operator("/", "/", O_BINARY, 2, s21_div));
  stack_operators_push(s, some_operator("mod", "m", O_BINARY, 2, s21_mod));

  stack_operators_push(s, some_operator("^", "^", O_BINARY, 3, s21_power));

  stack_operators_push(s, some_operator("sin", "s", O_UNARY, 4, s21_sin));
  stack_operators_push(s, some_operator("cos", "c", O_UNARY, 4, s21_cos));
  stack_operators_push(s, some_operator("tan", "t", O_UNARY, 4, s21_cos));
  stack_operators_push(s, some_operator("acos", "ac", O_UNARY, 4, s21_cos));
  stack_operators_push(s, some_operator("asin", "as", O_UNARY, 4, s21_cos));

  stack_operators_print_start(s);

  s21_calc(s);

  return 0;
}

void s21_calc(struct stack_operators* opers) {
  // char str[1000] = "6+3*(1+4*5)*2";
  char str[1000] = "6+3*(1+4*5)*2";
  double res = 0;
  struct list* polish_expression = NULL;
  enum va_error err = polish_format(opers, &polish_expression, str);
  if (err == VA_OK) polish_calc(opers, polish_expression, &res);
}