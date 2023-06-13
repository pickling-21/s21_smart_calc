#include "s21_operators.h"

// struct operator_info none_operator() {
//   return (const struct operator_info){.full_name = NULL,
//                                       .nat_name = NULL,
//                                       .o_type = O_NO_TYPE,
//                                       .priority = 0,
//                                       .func = NULL,
//                                       .assoc = ASSOC_LEFT};
// }

struct operator_info some_operator(const char* full_name, const char* nat_name,
                                   enum oper_type type, int priority,
                                   handler* func, enum assoc a) {
  return (struct operator_info){.full_name = full_name,
                                .nat_name = nat_name,
                                .o_type = type,
                                .priority = priority,
                                .func = func,
                                .assoc = a};
  ;
}

// void stack_operators_free_names(struct operator_info o) {
//   if (strcmp(o.full_name, "") != 0 && o.full_name != NULL) free(o.full_name);
//   if (strcmp(o.nat_name, "") != 0 && o.full_name != NULL) free(o.nat_name);
// }

// static void print_full_name(struct operator_info* o) {
//   o != NULL ? printf("%4s ", o->full_name) : printf("null");
// }
// static void print_nat_name(struct operator_info* o) {
//   o != NULL ? printf("%4s ", o->nat_name) : printf("null nat");
// }

/*--------------*/

bool stack_operators_create(size_t size, struct stack_operators* result) {
  bool err = false;
  result->data = NULL;
  result->count = 0;
  result->size = 0;
  if (size > 0) {
    result->data = malloc(sizeof(struct operator_info) * size);
    if (result->data != NULL) {
      result->size = size;
      err = true;
    }
  }
  return err;
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

bool stack_operators_is_empty(const struct stack_operators* s) {
  return s->count == 0;
}
bool stack_operators_is_full(const struct stack_operators* s) {
  return s->count == s->size;
}

void stack_operators_destroy(struct stack_operators* s) {
  if (s != NULL) {
    free(s->data);
    s->size = 0;
    s->count = 0;
  }
}

// static void stack_operators_foreach(struct stack_operators* s,
//                                     void(f)(struct operator_info*)) {
//   if (!stack_operators_is_empty(s)) {
//     for (size_t i = 0; i < s->count; i++) {
//       f(s->data + i);
//     }
//   }
// }

// void stack_operators_print_start(struct stack_operators* s) {
//   if (!stack_operators_is_empty(s)) {
//     stack_operators_foreach(s, print_full_name);
//     printf("\n");
//     stack_operators_foreach(s, print_nat_name);
//   }
// }

// void stack_operators_print(struct stack_operators* s) {
//   if (!stack_operators_is_empty(s)) {
//     stack_operators_foreach(s, print_full_name);
//   }
// }

/////////////

bool stack_ptr_operators_create(struct stack_ptr_operators* result,
                                size_t size) {
  bool err = false;
  if (result != NULL) {
    result->data = NULL;
    result->count = 0;
    result->size = 0;
    if (size > 0) {
      result->data = malloc(sizeof(struct operator_info*) * size);
      if (result->data != NULL) {
        result->size = size;
        err = true;
      }
    }
  }
  return err;
}

void stack_ptr_operators_destroy(struct stack_ptr_operators* s) {
  if (s != NULL) {
    free(s->data);
    s->size = 0;
    s->count = 0;
  }
}
bool stack_ptr_operators_is_full(const struct stack_ptr_operators* s) {
  return s->count == s->size;
}
bool stack_ptr_operators_is_empty(const struct stack_ptr_operators* s) {
  return s->count == 0;
}

static bool resize(struct stack_ptr_operators* s, size_t add) {
  bool err = false;
  s->size += add;
  s->data = realloc(s->data, s->size * sizeof(struct operator_info*));
  if (s->data != NULL) {
    err = true;
  }
  return err;
}

bool stack_ptr_operators_push(struct stack_ptr_operators* s,
                              struct operator_info* value) {
  bool result = true;
  if (stack_ptr_operators_is_full(s)) {
    result = resize(s, ADD_OPERS);
  }
  if (result) {
    s->data[s->count] = value;
    s->count = (s->count) + 1;
  }
  return result;
}

struct operator_info* stack_ptr_operators_pop(struct stack_ptr_operators* s) {
  struct operator_info* res = NULL;
  if (!stack_ptr_operators_is_empty(s)) {
    s->count--;
    res = s->data[s->count];
    s->data[s->count] = NULL;
    //?????free s.data[s.count]????
  }
  return res;
}

struct operator_info* stack_ptr_operators_last(struct stack_ptr_operators* s) {
  struct operator_info* result = NULL;
  if (!stack_ptr_operators_is_empty(s)) {
    result = s->data[s->count - 1];
  }
  return result;
}

// static void stack_ptr_operators_foreach(struct stack_ptr_operators* s,
//                                         void(f)(struct operator_info*)) {
//   if (!stack_ptr_operators_is_empty(s)) {
//     for (size_t i = 0; i < s->count; i++) {
//       f(s->data[i]);
//     }
//   } else {
//     printf("EMPTY!!!");
//   }
// }

// void stack_ptr_operators_print(struct stack_ptr_operators* s) {
//   if (!stack_ptr_operators_is_empty(s)) {
//     stack_ptr_operators_foreach(s, print_full_name);
//   } else {
//     printf("EMPTY!!!");
//   }
// }

// struct operator_info stack_operators_copy(const struct operator_info src) {
//   struct operator_info dst =
//       some_operator(src.full_name, src.nat_name, src.o_type, src.priority,
//                     src.func, src.assoc);
//   return dst;
// }

/*--------------*/

static bool find_full_name(struct operator_info* n, struct operator_info* h) {
  return strncmp(n->full_name, h->full_name, strlen(h->full_name)) == 0;
}
// static bool find_nat_name(struct operator_info* n, struct operator_info* h) {
//   return strncmp(n->nat_name, h->nat_name, strlen(h->nat_name)) == 0;
// }

static bool stack_ptr_operators_find(const struct stack_operators* haystack,
                                     struct operator_info needle, find f,
                                     struct stack_ptr_operators* s) {
  bool err = false;
  if (!stack_operators_is_empty(haystack)) {
    err = true;
    for (size_t i = 0; i < haystack->count && err == true; i++) {
      if (haystack->data[i].o_type != O_NO_TYPE) {
        if (f(&needle, &(haystack->data[i]))) {
          if (!stack_ptr_operators_push(s, &(haystack->data[i]))) err = false;
        }
      } else {
        printf("DEL_no_type");
      }
    }
  }
  return err;
}

// struct operator_info* stack_ptr_operators_find_nat_name(
//     const struct stack_operators* haystack, const char* str_needle) {
//   //????? Могут быть утечки?????
//   // Могу очищать то что не нужно и стэк не создался
//   struct operator_info* res = NULL;
//   struct operator_info needle =
//       some_operator(NULL, str_needle, O_NO_TYPE, 0, NULL, ASSOC_LEFT);
//   struct stack_ptr_operators stack = {0};
//   struct stack_ptr_operators* st = &stack;
//   bool err = stack_ptr_operators_create(st, QTY_OF_OPERS);
//   if (err) {
//     err = stack_ptr_operators_find(haystack, needle, find_nat_name, st);
//     res = st->data[0];
//   }
//   if (err) stack_ptr_operators_destroy(st);
//   return res;
// }

bool stack_ptr_operators_find_full_name(const struct stack_operators* haystack,
                                        const char* str_needle,
                                        struct stack_ptr_operators* st) {
  bool err = false;
  struct operator_info needle =
      some_operator(str_needle, NULL, O_NO_TYPE, 0, NULL, ASSOC_LEFT);
  err = stack_ptr_operators_find(haystack, needle, find_full_name, st);
  return err;
}
