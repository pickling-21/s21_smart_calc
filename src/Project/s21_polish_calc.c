#include "s21_polish_calc.h"

#include "s21_common.h"
#include "structs/s21_double.h"
#include "structs/s21_operators.h"
#include "structs/s21_structs.h"
#define DOUBLE_STACK_SIZE 300

enum va_error is_valid_num(struct maybe_num a) {
  enum va_error err = VA_OK;
  if (a.valid == M_N_INF) err = CALC_ERROR_NUM_INF;
  if (a.valid == M_N_NAN) err = CALC_ERROR_NUM_NAN;
  return err;
}

enum va_error polish_calc(struct list *polish_expression, double *result) {
  enum va_error error = VA_OK;
  struct stack_double stack;
  struct stack_double *st = &stack;

  struct maybe_num res_maybe_num = nan_num();
  if (stack_double_create(DOUBLE_STACK_SIZE, st)) {
    for (; polish_expression; polish_expression = polish_expression->next) {
      struct lexeme value = polish_expression->value;
      if (value.type == L_NUMBER) {
        stack_double_push(st, value.number);
      } else if (value.type == L_OPERATOR && is_operation(value.oper)) {
        struct operator_info *oper = value.oper;
        int delta = oper->o_type == O_UNARY ? st->count - 1 : st->count - 2;
        if (delta >= 0) {
          res_maybe_num = oper->func(st->data + delta);
          stack_double_pop(st);
          if (oper->o_type == O_BINARY) stack_double_pop(st);
          error = is_valid_num(res_maybe_num);
          stack_double_push(st, res_maybe_num.value);
        } else
          error = CALC_STACK_UNDERFLOW;
      }
    }

    if (error == VA_OK) {
      res_maybe_num = stack_double_pop(st);
      error = is_valid_num(res_maybe_num);
      if (error == VA_OK) {
        *result = res_maybe_num.value;
      }
      if (!stack_double_is_empty(st)) error = CALC_ERROR;
    }

    stack_double_destroy(st);
  } else
    error = MEM_MALLOC_RES;
  if (error != VA_OK) *result = 0.0;
  return error;
}
