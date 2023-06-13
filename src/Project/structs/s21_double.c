#include "s21_double.h"

#include "s21_structs.h"
/* double stack */
struct maybe_num nan_num() {
  return (struct maybe_num){.valid = M_N_NAN, .value = 0};
};
struct maybe_num inf_num() {
  return (struct maybe_num){.valid = M_N_INF, .value = 0};
};
struct maybe_num some_num(double i) {
  struct maybe_num res = {.valid = M_N_OK, .value = i};
  if (isinf(i)) res = inf_num();
  if (isnan(i)) res = nan_num();
  return res;
}

bool stack_double_create(size_t size, struct stack_double *result) {
  bool err = false;
  result->data = NULL;
  result->count = 0;
  result->size = 0;

  if (size > 0) {
    result->data = malloc(sizeof(double) * size);
    if (result->data) {
      result->size = size;
      err = true;
    }
  }
  return err;
}

void stack_double_destroy(struct stack_double *s) {
  if (s != NULL) {
    free(s->data);
    s->count = 0;
    s->data = 0;
  }
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
  struct maybe_num result = nan_num();
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

// void stack_double_print(const struct stack_double *s) {
//   for (size_t i = 0; i < s->count; i++) {
//     printf("%.10lf ", s->data[i]);
//   }
//   printf("\n");
// }

/*---------------------*/