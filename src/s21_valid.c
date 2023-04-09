// #include "s21_valid.h"

#include "s21_valid.h"

#include <stdlib.h>
#include <string.h>

#include "stack/s21_operators.h"
#define STACK_BRACKETS_SIZE 200

enum valid_erorrs validator(const char* str, char* res_str,
                            const struct stack_operators* opers) {
  enum valid_erorrs error = VA_OK;
  size_t len_str = strlen(str) + 1;
  res_str = malloc(sizeof(char) * len_str);
  struct str_info result = {.len = len_str, .str = res_str};
  if (result.str != NULL) {
    remove_spaces(str, result.str);
    replace_full_name(opers, &result);
  } else {
    error = VA_MALLOC_RES;
  }
  return error;
};

void remove_spaces(const char* str, char* result) {
  for (; *str != '\0'; str++) {
    if (!is_space(*str)) {
      *result = *str;
      result++;
    }
  }
  *result = '\0';
}

bool is_space(const char sym) { return sym == ' '; }

void replace_full_name(const struct stack_operators* opers,
                       struct str_info* res) {
  struct stack_operators* s = NULL;
  char* str = res->str;
  while (*str != '\0') {
    str++;
  }
}

struct operator_info check_operators_full_name(
    const struct stack_operators* opers, char const* str) {
  struct stack_operators* s = stack_operators_find_full_name(opers, str);
  struct operator_info res = none_operator();
  if (s->count > 1) {
    res = find_one(s, str);
  } else {
    res = s->data[0];
  }
  stack_operators_destroy(s);
  return res;
}

struct operator_info find_one(struct stack_operators* s, char const* str) {
  struct operator_info res = none_operator();
  for (size_t i = 0; i < s->count && res.o_type == O_NO_TYPE; i++) {
    struct operator_info curr = s->data[i];
    struct operator_info next = s->data[i + 1];
    if (unary_or_binanry_two(next, curr)) {
      if (strncmp(curr.full_name, str, strlen(curr.full_name)) == 0) {
        // если в самом начале строки, операция унарная
        res = unary_from_two(curr, next);
      } else {  // если после скобки то тоже унарная
            }
    }
  }
}
struct operator_info unary_from_two(struct operator_info curr,
                                    struct operator_info next) {
  return curr.o_type == O_UNARY ? curr : next;
}

bool unary_or_binanry_two(struct operator_info curr,
                          struct operator_info next) {
  return (curr.o_type == O_BINARY && next.o_type == O_UNARY) ||
         (curr.o_type == O_UNARY && next.o_type == O_BINARY);
}

// bool is_unary() {}

// bool brackets_okey(const char* str, const struct stack_operators* opers)
// {
//   bool res = true;
//   struct stack_operators stack =
//   stack_operators_create(STACK_BRACKETS_SIZE); struct stack_operators* s
//   = &stack; for (; *str != '\0' && res == true; str++) {
//     struct operator_info o = stack_operators_find_str(opers, str);
//     if (is_open_bracket(o)) stack_operators_push(s, o);
//     if (is_close_bracket) {
//       if (stack_operators_is_empty(s))
//         res = false;
//       else if (is_open_bracket(stack_operators_last(s))) {
//         stack_operators_pop(s);
//       }
//     }
//   }
//   if (!stack_operators_is_empty(s)) res = false;
//   return res;
// }

bool is_open_bracket(struct operator_info o) {
  return o.o_type == O_LEFT_BRACKET;
}

bool is_close_bracket(struct operator_info o) {
  return o.o_type == O_RIGHT_BRACKET;
}

void print_error(enum valid_erorrs err) {
  char* errr_message[] = {
      [VA_BRACKETS] = "неправильное количество скобок",
      [VA_MALLOC_RES] = "проблема с памятью, лучше перезапустить",
      [VA_OK] = "Вcе ок"};
  printf("%s\n", errr_message[err]);
}