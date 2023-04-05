
#include <stdio.h>

#include "s21_notation.h"
#include "s21_opers.h"
#include "s21_stek_queue.h"
#include "s21_valid.h"

int main() {
  struct stack_calc_opers s = stack_calc_opers_create(QTY_OF_OPERS);

  stack_calc_opers_push(&s, init(CAT_SIN, FUNC, 0, "sin", 1));
  stack_calc_opers_push(&s, init(CAT_COS, FUNC, 0, "cos", 1));
  stack_calc_opers_push(&s, init(CAT_LEFT, BRACKETS, 0, "(", 0));
  stack_calc_opers_push(&s, init(CAT_RIGHT, BRACKETS, 0, ")", 0));
  stack_calc_opers_push(&s, init(CAT_PLUS, SIMPLE, 1, "+", 2));
  stack_calc_opers_push(&s, init(CAT_MINUS, SIMPLE, 1, "-", 2));
  stack_calc_opers_push(&s, init(CAT_MUL, SIMPLE, 2, "*", 2));
  stack_calc_opers_push(&s, init(CAT_MOD, SIMPLE, 2, "mod", 2));
  stack_calc_opers_push(&s, init(CAT_DIV, SIMPLE, 2, "/", 2));
  stack_calc_opers_push(&s, init(CAT_POWER, SIMPLE, 3, "^", 2));
  stack_calc_opers_push(&s, init(CAT_COMMA, SEP, 0, ",", 0));

  char str[1000] = {0};
  scanf("%[^\n]", str);
  printf("START STR = %s\n", str);
  char *result = NULL;
  enum valid_erorrs error = validator(str, &result, &s);
  print_error(error);
  if (error == VA_OK) {
    printf("CHECK STRING = %s\n", result);
    struct list *a = inf_to_post(result, &s);
    list_foreach(a, print_symbols);
  } else {
    print_error(error);
  }
  free(result);
  return 0;
}
// 6+3*(1+4*5)*2