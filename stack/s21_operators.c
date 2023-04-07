#include "s21_operators.h"

struct operator_info none_operator() {
  return (const struct operator_info){.full_name = NULL,
                                      .nat_name = 0,
                                      .o_type = O_NO_TYPE,
                                      .priority = 0,
                                      .func = NULL};
}

struct operator_info some_operator(char* full_name, char nat_name,
                                   enum oper_type type, uint16_t priority,
                                   handler* func) {
  return (struct operator_info){.full_name = full_name,
                                .nat_name = nat_name,
                                .o_type = type,
                                .priority = priority,
                                .func = func};
}
/*--------------*/

struct stack_operators stack_operators_create(size_t size) {
  struct stack_operators result = {.data = NULL, .size = 0, .count = 0};
  if (size > 0) {
    result.data = malloc(sizeof(struct operator_info) * size);
    result.size = size;
  }
  return result;
}

void stack_operators_destroy(struct stack_operators* s) {
  free(s->data);
  s->size = 0;
  s->data = 0;
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

/*--------------*/

static void print_name(struct operator_info o) { printf("|%s|", o.full_name); }

void stack_operators_print(struct stack_operators* s) {
  stack_operators_foreach(s, print_name);
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

struct operator_info stack_operators_find_str(struct stack_operators* haystack,
                                              char* str_needle) {
  struct operator_info needle = none_operator();
  needle.full_name = str_needle;
  needle = stack_operators_find(haystack, needle, find_full_name);
  return needle;
}

struct operator_info stack_operators_find(struct stack_operators* haystack,
                                          struct operator_info needle, find f) {
  struct operator_info result = none_operator();
  if (!stack_operators_is_empty(haystack)) {
    for (size_t i = 0; i < haystack->count; i++) {
      if (f(needle, haystack->data[i])) {
        result = haystack->data[i];
        break;
      }
    }
  }
  return result;
}