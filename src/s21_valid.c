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
    replace_full_name(opers, str, result.str);
    struct stack_operators br = stack_operators_create(STACK_BRACKETS_SIZE);
    for (size_t i = 0; i < strlen(str) - 1 && error == VA_OK; i++) {
      if (is_digit(str[i])) continue;
      struct va_opers o = {
          .curr = stack_operators_find_nat_name(opers, str + i),
          .next = stack_operators_find_nat_name(opers, str + i + 1)};
      error = (brackets_okey(&br, o.curr) == false) ? VA_BRACKETS : VA_OK;
      error = check_opers(o, i);
    }
    if (stack_operators_is_empty(&br)) error = VA_BRACKETS;
    stack_operators_destroy(&br);
  } else {
    error = VA_MALLOC_RES;
  }
  return error;
};

bool check_opers(struct va_opers o, size_t i) {
  bool res = true;

  if (o.curr.o_type == O_BINARY && i == 0) res = false;
  if (o.curr.o_type == O_BINARY && o.next.o_type == O_BINARY) res = false;
  return res;
}

bool is_operator(struct operator_info o) {
  return o.o_type == O_BINARY || o.o_type == O_UNARY;
}

static bool is_digit(char c) { return (c >= '0' && c <= '9'); }

bool is_space(const char sym) { return sym == ' '; }

void replace_full_name(const struct stack_operators* opers, const char* str,
                       char* result) {
  bool open_br = false;
  for (size_t i = 0; *str != '\0'; i++) {
    if (!is_digit(*str)) {
      struct stack_operators* fr = stack_operators_find_full_name(opers, str);
      if (fr->count > 0) {
        if (fr->count == 1) {
          if (open_br == true) open_br = false;
          if (is_open_bracket(fr->data[0])) open_br = true;
          replace_and_write(&str, &result, fr->data[0].full_name,
                            fr->data[0].nat_name);
        } else {
          for (size_t j = 0; j < fr->count - 1; j++) {
            struct operator_info curr = fr->data[j];
            struct operator_info next = fr->data[j + 1];
            // если один из них унраный а другой нет,то:
            if (unary_or_binanry_two(curr, next)) {
              char* nat_name = unary_from_two(curr, next).nat_name;
              // если начало строки или сразу после скобки, то оставляем
              // унарный.
              if (i == 0 || open_br == true) {
                open_br = false;
              } else {
                nat_name = binary_from_two(curr, next).nat_name;
                // open_br false?
              }
              replace_and_write(&str, &result, curr.full_name, nat_name);
            }
          }
        }
      }
      stack_operators_destroy(fr);
    } else {
      open_br = false;
      if (!is_space(*str))
        *result++ = *str++;
      else
        str++;
    }
  }
  *result = '\0';
}

void replace_and_write(const char** str, char** res, char* full, char* nat) {
  size_t nat_len = strlen(nat);
  memcpy(*res, nat, nat_len);
  *str += strlen(full);
  *res += nat_len;
};

bool unary_or_binanry_two(struct operator_info curr,
                          struct operator_info next) {
  return (curr.o_type == O_BINARY && next.o_type == O_UNARY) ||
         (curr.o_type == O_UNARY && next.o_type == O_BINARY);
}

struct operator_info unary_from_two(struct operator_info curr,
                                    struct operator_info next) {
  return curr.o_type == O_UNARY ? curr : next;
}

struct operator_info binary_from_two(struct operator_info curr,
                                     struct operator_info next) {
  return curr.o_type == O_UNARY ? curr : next;
}

bool brackets_okey(struct stack_operators* br, struct operator_info o) {
  bool res = true;
  if (is_open_bracket(o)) stack_operators_push(br, o);
  if (is_close_bracket(o)) {
    if (stack_operators_is_empty(br)) {
      res = false;
    } else {
      stack_operators_pop(br);
    }
  }
  return res;
}

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