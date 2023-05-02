

#ifndef STRUCTS_S21_DOUBLE_H
#define STRUCTS_S21_DOUBLE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "../s21_common.h"

struct stack_double {
  size_t count;
  double *data;
  size_t size;
};

/* нужно для стек double??? */
enum stack_result {
  STACK_OK,
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
};
/*----------------*/
bool is_valid(struct maybe_num num);
/*double stack*/
// добавить функции арифметики (для чтения постфиксной нотации)
struct stack_double stack_double_create(size_t size);
void stack_double_destroy(struct stack_double *s);
bool stack_double_push(struct stack_double *s, double value);
struct maybe_num stack_double_pop(struct stack_double *s);
bool stack_double_is_empty(const struct stack_double *s);
bool stack_double_is_full(const struct stack_double *s);

#endif  // STRUCTS_S21_DOUBLE_H