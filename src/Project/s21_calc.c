#include "s21_calc.h"

#include <math.h>
#include <stdio.h>

#include "polish_format/s21_polish_format.h"
#include "s21_polish_calc.h"
#include "structs/s21_double.h"
#include "structs/s21_list.h"
// 6+3*(1+4*5)*2

struct maybe_num s21_negate(double* s) {
  return some_num(-1 * s[0]);
}
struct maybe_num s21_nothing(double* s) {
  return some_num(s[0]);
}

struct maybe_num s21_sum(double* s) {
  return some_num(s[0] + s[1]);
}
struct maybe_num s21_sub(double* s) {
  return some_num(s[0] - s[1]);
}

struct maybe_num s21_mul(double* s) {
  return some_num(s[0] * s[1]);
}
struct maybe_num s21_div(double* s) {
  return some_num(s[0] / s[1]);
}
struct maybe_num s21_mod(double* s) {
  return some_num(fmod(s[0], s[1]));
}

struct maybe_num s21_power(double* s) {
  return some_num(pow(s[0], s[1]));
}

struct maybe_num s21_sin(double* s) {
  return some_num(sin(s[0]));
}
struct maybe_num s21_cos(double* s) {
  return some_num(cos(s[0]));
}
struct maybe_num s21_tan(double* s) {
  return some_num(tan(s[0]));
}

struct maybe_num s21_asin(double* s) {
  return some_num(asin(s[0]));
}
struct maybe_num s21_acos(double* s) {
  return some_num(acos(s[0]));
}
struct maybe_num s21_atan(double* s) {
  return some_num(atan(s[0]));
}
struct maybe_num s21_sqrt(double* s) {
  return some_num(sqrt(s[0]));
}
struct maybe_num s21_ln(double* s) {
  return some_num(log(s[0]));
}
struct maybe_num s21_log(double* s) {
  return some_num(log10(s[0]));
}

enum va_error s21_calc(const char* str, double x, double* res) {
  struct stack_operators stack;
  *res = 0;
  struct stack_operators* s = &stack;
  enum va_error err = VA_OK;
  if (stack_operators_create(QTY_OF_OPERS, s)) {
    oper_push(s);
    struct list* polish_expression = NULL;
    err = polish_format(s, &polish_expression, str, x);
    if (err == VA_OK && polish_expression != NULL)
      err = polish_calc(polish_expression, res);
    list_destroy(polish_expression);
    stack_operators_destroy(s);
  }

  return err;
}

// int main() {
//   //       char start_string[256] = {"(838383-1232) -(299320930-1)"};
//   //   enum va_error err = VA_OK;
//   //   double result = 0;
//   //   err = s21_calc(start_string, X, &result);
//   //   ck_assert_int_eq(err, VA_OK);
//   //   ck_assert_double_eq_tol(result, -298483778, 7);
//   char start_string[256] = {"1+x"};
//   enum va_error err = VA_OK;
//   double result = 0;
//   printf("err = %d\n", err);
//   err = s21_calc(start_string, 1, &result);
//   printf("\n\n\nres = %lf\n", result);
// }

// double s21_calc(char* str) {
//   double res = 0;
//   printf("%s", str);
//   enum va_error a = VA_OK;
//   (void)a;
//   struct stack_operators stack;
//   struct stack_operators* s = &stack;
//   if (stack_operators_create(QTY_OF_OPERS, s)) {
//     oper_push(s);
//     struct list* inf_expression = NULL;
//     replace_full_name(s, str, &inf_expression);
//     validator(inf_expression);
//     struct list* polish_expression = NULL;
//     a = inf_to_post(inf_expression, &polish_expression);
//     list_destroy(polish_expression);
//     list_destroy(inf_expression);
//     stack_operators_destroy(s);
//   }
//   return res;
// }

// int main() {
//   printf("AAAA\n");
//   double res = s21_calc("sin(1)");
//   printf("\n\n\nRES = %lf\n-----------\n", res);
// }

void oper_push(struct stack_operators* s) {
  stack_operators_push(
      s, some_operator("(", "(", O_LEFT_BRACKET, 0, NULL, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator(")", ")", O_RIGHT_BRACKET, 0, NULL, ASSOC_LEFT));

  stack_operators_push(
      s, some_operator("+", "+", O_BINARY, 1, s21_sum, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("+", "#", O_UNARY, 6, s21_nothing, ASSOC_RIGHT));
  stack_operators_push(
      s, some_operator("-", "-", O_BINARY, 1, s21_sub, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("-", "~", O_UNARY, 6, s21_negate, ASSOC_RIGHT));
  stack_operators_push(
      s, some_operator("*", "*", O_BINARY, 2, s21_mul, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("/", "/", O_BINARY, 2, s21_div, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("mod", "m", O_BINARY, 2, s21_mod, ASSOC_LEFT));

  stack_operators_push(
      s, some_operator("^", "^", O_BINARY, 7, s21_power, ASSOC_RIGHT));

  stack_operators_push(
      s, some_operator("sin", "s", O_UNARY, 4, s21_sin, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("cos", "c", O_UNARY, 4, s21_cos, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("tan", "t", O_UNARY, 4, s21_tan, ASSOC_LEFT));

  stack_operators_push(
      s, some_operator("acos", "ac", O_UNARY, 4, s21_acos, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("asin", "as", O_UNARY, 4, s21_asin, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("atan", "at", O_UNARY, 4, s21_atan, ASSOC_LEFT));

  stack_operators_push(
      s, some_operator("sqrt", "qs", O_UNARY, 4, s21_sqrt, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("ln", "nl", O_UNARY, 4, s21_ln, ASSOC_LEFT));
  stack_operators_push(
      s, some_operator("log", "gl", O_UNARY, 4, s21_log, ASSOC_LEFT));
}
