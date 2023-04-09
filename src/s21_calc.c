#include "s21_calc.h"

#include <stdio.h>

#include "s21_notation.h"
#include "s21_valid.h"
#include "stack/s21_list.h"
#include "stack/s21_operators.h"

int main() {
  struct stack_operators s = stack_operators_create(QTY_OF_OPERS);
  stack_operators_push(&s, some_operator("+", "+", O_BINARY, 1, NULL));
  stack_operators_push(&s, some_operator("+", "#", O_UNARY, 6, NULL));
  stack_operators_push(&s, some_operator("-", "-", O_BINARY, 1, NULL));
  stack_operators_push(&s, some_operator("-", "~", O_UNARY, 6, NULL));

  stack_operators_push(&s, some_operator("*", "*", O_BINARY, 2, NULL));
  stack_operators_push(&s, some_operator("/", "/", O_BINARY, 2, NULL));
  stack_operators_push(&s, some_operator("mod", "m", O_BINARY, 2, NULL));

  stack_operators_push(&s, some_operator("^", "^", O_BINARY, 3, NULL));

  stack_operators_push(&s, some_operator("sin", "s", O_UNARY, 4, NULL));
  stack_operators_push(&s, some_operator("cos", "c", O_UNARY, 4, NULL));

  char str[1000] = {0};
  scanf("%[^\n]", str);
  printf("START STR = %s\n", str);
  char *res_str = NULL;
  enum valid_erorrs error = validator(str, res_str, &s);
  print_error(error);
  if (error == VA_OK) {
    printf("CHECK STRING = %s\n", result);
    struct list *a = inf_to_post(result, &s);
    list_print(a);
  } else {
    print_error(error);
  }
  if (error != VA_MALLOC_RES) free(res_str);
  return 0;
}
// 6+3*(1+4*5)*2