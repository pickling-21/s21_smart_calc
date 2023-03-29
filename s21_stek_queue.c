#include "s21_stek_queue.h"

#include <stdio.h>
#include <stdlib.h>

struct maybe_sign some_sign(char i) { return (struct maybe_sign){i, true}; }
const struct maybe_sign none_sign = {0};

struct maybe_num some_num(double i) { return (struct maybe_num){i, true}; }
const struct maybe_num none_num = {0};

const struct stack_interface stack_c = {
    .char_st = {stack_char_create, stack_char_is_empty, stack_char_is_full,
                stack_char_destroy, stack_char_push, stack_char_pop}};

const struct stack_interface stack_d = {
    .double_st = {stack_double_create, stack_double_is_empty,
                  stack_double_is_full, stack_double_destroy, stack_double_push,
                  stack_double_pop}};

const char *const stack_error_messages[] = {
    [STACK_OVERFLOW] = "Не хватает места, стек заполнен",
    [STACK_UNDERFLOW] =
        "В стеке слишком мало элементов для совершения операции",
};

/* double stack */
struct stack_double stack_double_create(size_t size) {
  struct stack_double result = {0, NULL, 0};
  if (size > 0) {
    result.data = malloc(sizeof(struct stack_double) * size);
    result.size = size;
  }
  return result;
}

void stack_double_destroy(struct stack_double *s) {
  free(s->data);
  s->count = 0;
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
  struct maybe_num result = none_num;
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

/* char stack*/
struct stack_char stack_char_create(size_t size) {
  struct stack_char result = {0, NULL, 0};
  if (size > 0) {
    result.data = malloc(sizeof(struct stack_char) * size);
    result.size = size;
  }
  return result;
}

void stack_char_destroy(struct stack_char *s) {
  free(s->data);
  s->count = 0;
};

bool stack_char_push(struct stack_char *s, double value) {
  bool result = false;
  if (!stack_char_is_full(s)) {
    s->data[s->count] = value;
    s->count = (s->count) + 1;
    result = true;
  }
  return result;
}

struct maybe_sign stack_char_pop(struct stack_char *s) {
  struct maybe_sign result = none_sign;
  if (!stack_char_is_empty(s)) {
    s->count--;
    result = some_sign(s->data[s->count]);
    s->data[s->count] = 0;
  }
  return result;
}

bool stack_char_is_full(const struct stack_char *s) {
  return (*s).count == (*s).size;
}
// Стек пустой
bool stack_char_is_empty(const struct stack_char *s) { return (*s).count == 0; }

/* list(queune)*/

void print_int64_space(double i) {
  printf("%lf", i);
  printf(" ");
}

struct list *node_create(struct symbols value) {
  struct list *list = malloc(sizeof(struct list));
  if (list) {
    list->value = value;
    list->next = NULL;
  }
  return list;
}

void list_add_front(struct list **old, struct symbols value) {
  struct list *new = node_create(value);
  if (old != NULL) {
    new->next = *old;
    *old = new;
  }
}

size_t list_length(struct list const *const list) {
  size_t len = 0;
  struct list *tmp = (struct list *)list;
  for (; tmp; len++, tmp = tmp->next)
    ;
  return len;
}

void list_destroy(struct list *list) {
  while (list) {
    struct list *temp = NULL;
    temp = list->next;
    free(list);
    list = temp;
  }
  if (list != NULL) free(list);
}

struct list *list_last(struct list *list) {
  while (list && list->next) {
    list = list->next;
  }
  return list;
}

void list_add_back(struct list **old, struct symbols value) {
  if (*old != NULL) {
    list_last(*old)->next = node_create(value);
  } else {
    list_add_front(old, value);
  }
}
void list_foreach(struct list const *l, void(f)(double)) {
  while (l) {
    f(l->value.number);
    l = l->next;
  }
}

/*---------------------*/