#include "s21_polish_calc.h"

#include "s21_common.h"
#include "structs/s21_double.h"
#include "structs/s21_operators.h"
#define DOUBLE_STACK_SIZE 300
enum va_error polish_calc(const struct stack_operators *opers,
                          struct list *polish_expression, double *result) {
  printf("POLISH_CALC\n");
  list_print(polish_expression);
  struct lexeme a = list_pop_front(&polish_expression);
  printf("LEXEME\n");
  print_lexeme(a);
  printf("\n");
  list_print(polish_expression);
  struct stack_double st = stack_double_create(DOUBLE_STACK_SIZE);

  while (polish_expression) {
    struct lexeme value = list_pop_front(&polish_expression);
    if (a.type == L_NUMBER) {
      stack_double_push(&st, value.number);
    }
    if (a.type == L_OPERATOR) {
      double arr[2] = {0};
      if (a.oper.o_type = O_BINARY) {
        arr[0] = st.data[st.count - 2];
        arr[1] = st.data[st.count - 1];
      }
      // stack_double_push(st, );
      struct maybe_num res = a.oper.func(arr);
    }
  }
  stack_double_destroy(&st);
  return 1;
}
