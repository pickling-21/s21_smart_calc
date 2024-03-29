

#ifndef STRUCTS_S21_DOUBLE_H
#define STRUCTS_S21_DOUBLE_H
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_structs.h"
struct maybe_num nan_num();
struct maybe_num some_num(double i);
struct maybe_num inf_num();

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
// bool is_valid(struc maybe_num num);
/*double stack*/
// добавить функции арифметики (для чтения постфиксной нотации)
bool stack_double_create(size_t size, struct stack_double *result);
void stack_double_destroy(struct stack_double *s);
bool stack_double_push(struct stack_double *s, double value);
struct maybe_num stack_double_pop(struct stack_double *s);
bool stack_double_is_empty(const struct stack_double *s);
bool stack_double_is_full(const struct stack_double *s);

void stack_double_print(const struct stack_double *s);
#endif  // STRUCTS_S21_DOUBLE_H