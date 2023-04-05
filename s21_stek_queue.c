#include "s21_stek_queue.h"

#include <stdio.h>
#include <stdlib.h>

const struct maybe_num none_num = {0};
struct maybe_num some_num(double i) {
  return (struct maybe_num){.valid = true, .value = i};
}

// const struct stack_interface stack_d = {
//     .double_st = {stack_double_create, stack_double_is_empty,
//                   stack_double_is_full, stack_double_destroy,
//                   stack_double_push, stack_double_pop}};

const char *const stack_error_messages[] = {
    [STACK_OVERFLOW] = "Не хватает места, стек заполнен",
    [STACK_UNDERFLOW] =
        "В стеке слишком мало элементов для совершения операции",
};

struct symbols some_oper(enum oper_category o) {
  return (struct symbols){.type = S_OPERATION, .operator= o };
};

struct symbols some_number(double i) {
  return (struct symbols){.type = S_NUMBER, .number = i};
};

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

/* operators stack*/
struct stack_operators stack_operators_create(size_t size) {
  struct stack_operators result = {0, NULL, 0};
  if (size > 0) {
    result.data = malloc(sizeof(enum oper_category) * size);
    result.size = size;
  }
  return result;
}

void stack_operators_destroy(struct stack_operators *s) {
  free(s->data);
  s->size = 0;
  s->count = 0;
};

bool stack_operators_push(struct stack_operators *s, enum oper_category value) {
  bool result = false;
  if (!stack_operators_is_full(s)) {
    s->data[s->count] = value;
    s->count = (s->count) + 1;
    result = true;
  }
  return result;
}

enum oper_category stack_operators_pop(struct stack_operators *s) {
  enum oper_category result = CAT_NONE;
  if (!stack_operators_is_empty(s)) {
    s->count--;
    result = s->data[s->count];
    s->data[s->count] = CAT_NONE;
  }
  return result;
}

enum oper_category stack_operators_last(struct stack_operators *s) {
  enum oper_category result = CAT_NONE;
  if (!stack_operators_is_empty(s)) {
    result = s->data[s->count - 1];
  }
  return result;
}

bool stack_operators_is_full(const struct stack_operators *s) {
  return s->count == s->size;
}
// Стек пустой
bool stack_operators_is_empty(const struct stack_operators *s) {
  return s->count == 0;
}

void stack_operators_print(struct stack_operators *s) {
  const char *const oper_sym[] = {
      [CAT_LEFT] = "(",  [CAT_RIGHT] = ")", [CAT_PLUS] = "+",
      [CAT_MINUS] = "-", [CAT_MUL] = "*",   [CAT_DIV] = "/",
      [CAT_MOD] = "mod", [CAT_POWER] = "^", [CAT_SIN] = "sin"};
  for (size_t i = 0; i < s->count; i++) {
    printf("%s ", oper_sym[s->data[i]]);
  }
}

/* list(queune)*/

void print_int64_space(double i) {
  printf("%lf", i);
  printf(" ");
}

void print_symbols(struct symbols i) {
  const char *const oper_sym_s[] = {
      [CAT_LEFT] = "(",  [CAT_PLUS] = "+",  [CAT_MINUS] = "-",
      [CAT_MUL] = "*",   [CAT_DIV] = "/",   [CAT_MOD] = "mod",
      [CAT_POWER] = "^", [CAT_SIN] = "sin", [CAT_COS] = "cos",
      [CAT_RIGHT] = ")", [CAT_COMMA] = ","};

  if (i.type == S_NUMBER) {
    print_int64_space(i.number);
  } else if (i.type == S_OPERATION) {
    printf("%s ", oper_sym_s[i.operator]);
  }
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
void list_foreach(struct list const *l, void(f)(struct symbols)) {
  while (l) {
    f(l->value);
    l = l->next;
  }
}

/*---------------------*/

bool last_from_stack_to_list(struct list *l, struct stack_operators *s) {
  bool result = false;
  enum oper_category o = stack_operators_pop(s);
  if (o != CAT_NONE) {
    list_add_back(&l, some_oper(o));
    result = true;
  }
  return result;
}

void push_to_list_until(bool f(enum oper_category, enum oper_category),
                        struct list *l, struct stack_operators *s) {}