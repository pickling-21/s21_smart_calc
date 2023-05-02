#include "s21_operators.h"

struct operator_info none_operator() {
  return (const struct operator_info){.full_name = NULL,
                                      .nat_name = NULL,
                                      .o_type = O_NO_TYPE,
                                      .priority = 0,
                                      .func = NULL};
}

struct operator_info some_operator(const char* full_name, const char* nat_name,
                                   enum oper_type type, uint16_t priority,
                                   handler* func) {
  if (full_name == NULL) full_name = "";
  if (nat_name == NULL) nat_name = "";
  return (struct operator_info){.full_name = strdup(full_name),
                                .nat_name = strdup(nat_name),
                                .o_type = type,
                                .priority = priority,
                                .func = func};
}

static void free_names(struct operator_info o) {
  if (strcmp(o.full_name, "") != 0 && o.full_name != NULL) free(o.full_name);
  if (strcmp(o.nat_name, "") != 0 && o.full_name != NULL) free(o.nat_name);
}

static void print_full_name(struct operator_info o) {
  printf("%4s ", o.full_name);
}
static void print_nat_name(struct operator_info o) {
  printf("%4s ", o.nat_name);
}

/*--------------*/

struct stack_operators stack_operators_create(size_t size) {
  struct stack_operators result = {.data = NULL, .size = 0, .count = 0};
  if (size > 0) {
    result.data = malloc(sizeof(struct operator_info) * size);
    if (result.data != NULL) result.size = size;
  }
  return result;
}

void stack_operators_destroy(struct stack_operators* s) {
  if (s != NULL) {
    stack_operators_foreach(s, free_names);
    free(s->data);
    s->size = 0;
    s->data = 0;
  }
}

bool stack_operators_push(struct stack_operators* s,
                          struct operator_info value) {
  bool result = false;
  if (!stack_operators_is_full(s)) {
    s->data[s->count] = value;
    s->count = (s->count) + 1;
    result = true;
  }
  return result;
}
struct operator_info stack_operators_pop(struct stack_operators* s) {
  struct operator_info result = none_operator();
  if (!stack_operators_is_empty(s)) {
    s->count--;
    result = s->data[s->count];
    s->data[s->count] = none_operator();
  }
  return result;
}

bool stack_operators_is_empty(const struct stack_operators* s) {
  return s->count == 0;
}
bool stack_operators_is_full(const struct stack_operators* s) {
  return s->count == s->size;
}

struct operator_info stack_operators_last(struct stack_operators* s) {
  struct operator_info result = none_operator();
  if (!stack_operators_is_empty(s)) {
    result = s->data[s->count - 1];
  }
  return result;
}

struct operator_info stack_operators_copy(const struct operator_info src) {
  struct operator_info dst = some_operator(src.full_name, src.nat_name,
                                           src.o_type, src.priority, src.func);
  return dst;
}

/*--------------*/

void stack_operators_print_start(struct stack_operators* s) {
  if (!stack_operators_is_empty(s)) {
    stack_operators_foreach(s, print_full_name);
    printf("\n");
    stack_operators_foreach(s, print_nat_name);
  }
}

void stack_operators_print(struct stack_operators* s) {
  if (!stack_operators_is_empty(s)) {
    stack_operators_foreach(s, print_full_name);
  }
}

void stack_operators_foreach(struct stack_operators* s,
                             void(f)(struct operator_info)) {
  if (!stack_operators_is_empty(s)) {
    for (size_t i = 0; i < s->count; i++) {
      f(s->data[i]);
    }
  }
}
static bool find_full_name(struct operator_info n, struct operator_info h) {
  return strncmp(n.full_name, h.full_name, strlen(h.full_name)) == 0;
}
static bool find_nat_name(struct operator_info n, struct operator_info h) {
  return strncmp(n.nat_name, h.nat_name, strlen(h.nat_name)) == 0;
}

struct operator_info stack_operators_find_nat_name(
    const struct stack_operators* haystack, const char* str_needle) {
  struct operator_info needle =
      some_operator(NULL, str_needle, O_NO_TYPE, 0, NULL);
  struct stack_operators fr =
      stack_operators_find(haystack, needle, find_nat_name);
  free_names(needle);
  struct operator_info res = stack_operators_copy(fr.data[0]);
  stack_operators_destroy(&fr);
  return res;
}

struct stack_operators stack_operators_find_full_name(
    const struct stack_operators* haystack, const char* str_needle) {
  struct operator_info needle =
      some_operator(str_needle, NULL, O_NO_TYPE, 0, NULL);
  struct stack_operators res =
      stack_operators_find(haystack, needle, find_full_name);
  free_names(needle);
  return res;
}

struct stack_operators stack_operators_find(
    const struct stack_operators* haystack, struct operator_info needle,
    find f) {
  struct stack_operators result = stack_operators_create(QTY_OF_OPERS);
  struct stack_operators* res = &result;
  if (!stack_operators_is_empty(haystack)) {
    for (size_t i = 0; i < haystack->count; i++) {
      if (haystack->data[i].o_type != O_NO_TYPE) {
        if (f(needle, haystack->data[i])) {
          stack_operators_push(res, stack_operators_copy(haystack->data[i]));
        }
      } else {
        printf("DEL_no_type");
      }
    }
  }
  return result;
}
