#include "s21_double.h"

#include "../s21_common.h"

/* double stack */

struct stack_double stack_double_create(size_t size) {
  struct stack_double result = {0, NULL, 0};
  if (size > 0) {
    result.data = malloc(sizeof(double) * size);
    result.size = size;
  }
  return result;
}

void stack_double_destroy(struct stack_double *s) {
  free(s->data);
  s->count = 0;
  s->size = 0;
};

bool stack_double_push(struct stack_double *s, double value) {
  bool result = false;
  if (!stack_double_is_full(s)) {
    s->data[s->count] = value;
    s->count = (s->count) + 1;
    result = true;
  }
  return result;
}

struct maybe_num stack_double_pop(struct stack_double *s) {
  struct maybe_num result = none_num();
  if (!stack_double_is_empty(s)) {
    s->count--;
    result = some_num(s->data[s->count]);
    s->data[s->count] = 0;
  }
  return result;
}

bool stack_double_is_full(const struct stack_double *s) {
  return (*s).count == (*s).size;
}
// Стек пустой
bool stack_double_is_empty(const struct stack_double *s) {
  return (*s).count == 0;
}

/*---------------------*/