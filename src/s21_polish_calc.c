#include "s21_polish_calc.h"

#include "s21_common.h"
#include "stack/s21_double.h"
#include "stack/s21_operators.h"

enum va_error polish_calc(const struct stack_operators *opers,
                          struct list *polish_expression, double *result) {
  printf("POLISH_CALC\n");
  list_print(polish_expression);
  struct lexeme a = list_pop_first(polish_expression);
  a.type == L_NO_TYPE ? printf("NO_TYPE\n") : print_lexeme(a);
  list_print(polish_expression);
  return 1;
}