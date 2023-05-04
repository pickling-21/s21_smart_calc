#include "s21_polish_calc.h"

#include "s21_common.h"
#include "structs/s21_double.h"
#include "structs/s21_operators.h"
#include "structs/s21_structs.h"
#define DOUBLE_STACK_SIZE 300
enum va_error polish_calc(const struct stack_operators *opers,
                          struct list *polish_expression, double *result) {
  enum va_error error = VA_OK;
  printf("POLISH_CALC\n");
  list_print(polish_expression);
  printf("\n");
  printf("\nSTART\n");
  struct stack_double st = stack_double_create(DOUBLE_STACK_SIZE);
  if (st.data) {
    while (polish_expression && error == VA_OK) {
      struct lexeme value = list_pop_front(&polish_expression);
      if (value.type == L_NUMBER) {
        stack_double_push(&st, value.number);
      } else if (value.type == L_OPERATOR && (value.oper.o_type == O_BINARY ||
                                              value.oper.o_type == O_UNARY)) {
        struct maybe_num res_maybe_num = nan_num();
        int64_t delta =
            value.oper.o_type == O_UNARY ? st.count - 1 : st.count - 2;
        if (delta >= 0) {
          res_maybe_num = value.oper.func(st.data + delta);
          stack_double_pop(&st);
          if (value.oper.o_type == O_BINARY) stack_double_pop(&st);
          if (res_maybe_num.valid == M_N_OK) {
            stack_double_push(&st, res_maybe_num.value);
          } else {
            error = VA_ERROR_NUM;
          }
        } else {
          error = VA_STACK_UNDERFLOW;
        }
      } else {
        error = VA_NO_OPER;
      }
      list_print(polish_expression);
      printf("\n stacke = ");
      stack_double_print(&st);
      printf("\n");
    }
  } else {
    error = VA_MALLOC_RES;
  }
  if (!stack_double_is_empty) error = VA_ERROR_CALC;
  printf("result = ");
  stack_double_print(&st);
  stack_double_destroy(&st);
  return error;
}