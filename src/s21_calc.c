#include "s21_calc.h"

#include <stdio.h>

#include "polish_format/s21_polish_format.h"
#include "s21_polish_calc.h"
#include "stack/s21_list.h"
// 6+3*(1+4*5)*2

int main() {
  struct stack_operators stack = stack_operators_create(QTY_OF_OPERS);
  struct stack_operators* s = &stack;
  stack_operators_push(s, some_operator("(", "(", O_LEFT_BRACKET, 0, NULL));
  stack_operators_push(s, some_operator(")", ")", O_RIGHT_BRACKET, 0, NULL));

  stack_operators_push(s, some_operator("+", "+", O_BINARY, 1, NULL));
  stack_operators_push(s, some_operator("+", "#", O_UNARY, 6, NULL));
  stack_operators_push(s, some_operator("-", "-", O_BINARY, 1, NULL));
  stack_operators_push(s, some_operator("-", "~", O_UNARY, 6, NULL));

  stack_operators_push(s, some_operator("*", "*", O_BINARY, 2, NULL));
  stack_operators_push(s, some_operator("/", "/", O_BINARY, 2, NULL));
  stack_operators_push(s, some_operator("mod", "m", O_BINARY, 2, NULL));

  stack_operators_push(s, some_operator("^", "^", O_BINARY, 3, NULL));

  stack_operators_push(s, some_operator("sin", "s", O_UNARY, 4, NULL));
  stack_operators_push(s, some_operator("cos", "c", O_UNARY, 4, NULL));

  stack_operators_print_start(s);

  s21_calc(s);

  return 0;
}

void s21_calc(struct stack_operators* opers) {
  // char str[1000] = "6+3*(1+4*5)*2";
  char str[1000] = "6+3*(1+4*5)*2";

  double res = 0;
  struct list* polish_expression = NULL;
  enum va_error err = polish_format(opers, polish_expression, str);
  if (err == VA_OK) polish_calc(opers, polish_expression, &res);
}