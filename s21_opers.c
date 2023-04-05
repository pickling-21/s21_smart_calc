#include "s21_opers.h"
const struct calc_oper non_calc_oper() {
  return (const struct calc_oper){.category = CAT_NONE,
                                  .lenght = 0,
                                  .priority = 0,
                                  .type = NO_OPER_TYPE,
                                  .name = NULL,
                                  .min_qty_opers = 0};
};

struct stack_calc_opers stack_calc_opers_create(size_t sz) {
  struct stack_calc_opers result = {0, NULL, 0};
  if (sz > 0) {
    result.data = malloc(sizeof(struct calc_oper) * sz);
    result.size = sz;
  }
  return result;
}

bool stack_calc_opers_push(struct stack_calc_opers *s, struct calc_oper value) {
  bool result = false;
  if (!stack_calc_opers_full(s)) {
    s->data[s->count] = value;
    s->count = (s->count) + 1;
    result = true;
  }
  return result;
}

struct calc_oper init(enum oper_category category, enum oper_type type,
                      int8_t priority, char *name, size_t min_qty_opers) {
  size_t len = strlen(name);
  return (struct calc_oper){.category = category,
                            .type = type,
                            .priority = priority,
                            .name = name,
                            .lenght = len,
                            .min_qty_opers = min_qty_opers};
}

void stack_calc_opers_destroy(struct stack_calc_opers *s) {
  free(s->data);
  s->size = 0;
  s->count = 0;
}

bool stack_calc_opers_full(const struct stack_calc_opers *s) {
  return s->count == s->size;
}

bool find_category(struct calc_oper needle, struct calc_oper haystack) {
  return needle.category == haystack.category ? true : false;
}

bool find_priority(struct calc_oper needle, struct calc_oper haystack) {
  return needle.priority == haystack.priority ? true : false;
}

bool find_type(struct calc_oper needle, struct calc_oper haystack) {
  return needle.type == haystack.type ? true : false;
}

bool find_name(struct calc_oper needle, struct calc_oper haystack) {
  return strncmp(needle.name, haystack.name, haystack.lenght) == 0 ? true
                                                                   : false;
}

struct calc_oper stack_calc_opers_find(struct calc_oper needle,
                                       const struct stack_calc_opers *s,
                                       find f) {
  struct calc_oper result = (struct calc_oper)non_calc_oper();
  for (int i = 0, flag = 0; i < s->count && flag == 0; i++) {
    if (f(needle, s->data[i])) {
      result = s->data[i];
      flag = 1;
    }
  }
  return result;
}
enum oper_category operator_check(char const *str, char **end,
                                  const struct stack_calc_opers *s) {
  *end = (char *)str;
  struct calc_oper to_find = non_calc_oper();
  to_find.name = str;
  struct calc_oper result = stack_calc_opers_find(to_find, s, find_name);
  *end += result.lenght;
  return result.category;
}

enum oper_type operator_type(enum oper_category cat,
                             const struct stack_calc_opers *s) {
  struct calc_oper to_find = non_calc_oper();
  to_find.category = cat;
  return stack_calc_opers_find(to_find, s, find_category).type;
}