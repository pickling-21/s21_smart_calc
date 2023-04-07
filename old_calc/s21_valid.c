#include "s21_valid.h"

#include <stdlib.h>
#include <string.h>

#include "s21_notation.h"
#include "s21_opers.h"
#include "s21_stek_queue.h"

#define BRACKETS_SIZE 1000

// const struct oper opers_s[QTY_OF_OPERS] = {
//     [CAT_NONE] = {.category = CAT_NONE,
//                   .lenght = 0,
//                   .priority = 0,
//                   .type = NO_OPER_TYPE,
//                   .name = NULL},
//     [CAT_SIN] = {.category = CAT_SIN,
//                  .type = FUNC,
//                  .priority = 0,
//                  .lenght = 3,
//                  .name = "sin"},
//     [CAT_COS] = {.category = CAT_COS,
//                  .type = FUNC,
//                  .priority = 0,
//                  .lenght = 3,
//                  .name = "cos"},
//     [CAT_LEFT] = {.category = CAT_LEFT,
//                   .lenght = 1,
//                   .priority = 0,
//                   .name = "(",
//                   .type = BRACKETS},
//     [CAT_RIGHT] = {.category = CAT_RIGHT,
//                    .lenght = 1,
//                    .priority = 0,
//                    .name = ")",
//                    .type = BRACKETS},
//     [CAT_PLUS] = {.category = CAT_PLUS,
//                   .lenght = 1,
//                   .priority = 1,
//                   .name = "+",
//                   .type = SIMPLE},
//     [CAT_MINUS] = {.category = CAT_MINUS,
//                    .lenght = 1,
//                    .priority = 1,
//                    .name = "-",
//                    .type = SIMPLE},
//     [CAT_MUL] = {.category = CAT_MUL,
//                  .lenght = 1,
//                  .priority = 2,
//                  .name = "*",
//                  .type = SIMPLE},
//     [CAT_MOD] = {.category = CAT_MOD,
//                  .type = SIMPLE,
//                  .priority = 2,
//                  .lenght = 3,
//                  .name = "mod"},
//     [CAT_DIV] = {.category = CAT_DIV,
//                  .type = SIMPLE,
//                  .priority = 2,
//                  .lenght = 1,
//                  .name = "/"},
//     [CAT_POWER] = {.category = CAT_POWER,
//                    .type = SIMPLE,
//                    .priority = 3,
//                    .lenght = 1,
//                    .name = "^"},
//     [CAT_COMMA] = {.category = CAT_COMMA,
//                    .type = SEP,
//                    .priority = 0,
//                    .lenght = 1,
//                    .name = ","},

// };

enum valid_erorrs validator(const char* str, char** res_str,
                            const struct stack_calc_opers* opers) {
  enum valid_erorrs error = VA_OK;
  size_t len_str = strlen(str) + 1;
  res_str = malloc(sizeof(char) * len_str);
  struct str_info result = {.len = len_str, .str = res_str};

  if (result.str != NULL) {
    remove_spaces(str, *result.str);
    printf("string witout spaces = %s\n", *result.str);
    error = brackets_okey(*result.str) == true ? VA_OK : VA_BRACKETS;
    if (error == VA_OK) replace_unary_minus(result.str);
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

void replace_unary_minus(char* str) {
  if (*str == '-') *str = '~';
  for (; *str != '\0'; str++) {
    if (*str == '(' && *(str + 1) == '-') *(str + 1) = '~';
  }
}

bool brackets_okey(const char* str) {
  bool res = true;
  struct stack_operators stack = stack_operators_create(BRACKETS_SIZE);
  struct stack_operators* s = &stack;
  for (; *str != '\0' && res == true; str++) {
    // printf("%d %s\n", i, str);
    if (is_open_bracket(*str))
      stack_operators_push(s, (struct read_notation){CAT_LEFT, BRACKETS, 0});
    if (is_close_bracket(*str)) {
      if (stack_operators_is_empty(s)) {
        res = false;
      } else if (stack_operators_last(s).category == CAT_LEFT) {
        stack_operators_pop(s);
      }
    }
  }
  if (!stack_operators_is_empty(s)) res = false;
  return res;
}

bool is_open_bracket(char s) { return s == '('; }

bool is_close_bracket(char s) { return s == ')'; }

void print_error(enum valid_erorrs err) {
  char* errr_message[] = {
      [VA_BRACKETS] = "неправильное количество скобок",
      [VA_MALLOC_RES] = "проблема с памятью, лучше перезапустить",
      [VA_OK] = "Вcе ок"};
  printf("%s\n", errr_message[err]);
}