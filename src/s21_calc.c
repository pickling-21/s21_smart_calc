#include "s21_calc.h"

#include <stdio.h>

#include "s21_notation.h"
#include "stack/s21_list.h"
#include "valid/s21_valid.h"
// 6+3*(1+4*5)*2

int main() {
  struct stack_operators stack = stack_operators_create(QTY_OF_OPERS);
  struct stack_operators* s = &stack;
  stack_operators_push(s, some_operator("(", "(", O_LEFT_BRACKET, 0, NULL));
  stack_operators_push(s, some_operator(")", ")", O_RIGHT_BRACKET, 0, NULL));

  stack_operators_push(s, some_operator("+", "+", O_BINARY, 1, NULL));
  stack_operators_push(s, some_operator("+", "#", O_UNARY, 6, NULL));
  stack_operators_push(s, some_operator("-", "-", O_BINARY, 1, NULL));
  stack_operators_push(s, some_operator("-", "~", O_UNARY, 6, NULL));

  stack_operators_push(s, some_operator("*", "*", O_BINARY, 2, NULL));
  stack_operators_push(s, some_operator("/", "/", O_BINARY, 2, NULL));
  stack_operators_push(s, some_operator("mod", "m", O_BINARY, 2, NULL));

  stack_operators_push(s, some_operator("^", "^", O_BINARY, 3, NULL));

  stack_operators_push(s, some_operator("sin", "s", O_UNARY, 4, NULL));
  stack_operators_push(s, some_operator("cos", "c", O_UNARY, 4, NULL));

  stack_operators_print_start(s);

  s21_calc(s);

  return 0;
}

void s21_calc(struct stack_operators* s) {
  char str[1000] = {0};
  scanf("%[^\n]", str);
  printf("START STR = %s\n", str);

  char* res_str = NULL;
  size_t len_str = strlen(str) + 1;
  res_str = malloc(sizeof(char) * len_str);
  enum va_error error = VA_OK;
  if (res_str == NULL) error = VA_MALLOC_RES;
  if (error == VA_OK) {
    error = replace_full_name(s, str, res_str);
    printf("replaced str = %s\n", res_str);
    printf("segasss\n");
    if (error == VA_OK) {
      error = validator(res_str, s);
      printf("validdd\n");
      print_error(error);

      if (error == VA_OK) {
        printf("CHECK STRING = %s\n", res_str);
        struct list* a = inf_to_post(res_str, s);
        list_print(a);
      }
    }
  }
  print_error(error);
  if (error != VA_MALLOC_RES) free(res_str);
}

void print_error(enum va_error err) {
  char* errr_message[] = {
      [VA_BRACKETS] = "неправильное количество скобок",
      [VA_MALLOC_RES] = "проблема с памятью, лучше перезапустить",
      [VA_OK] = "Вcе ок",
      [VA_NO_OPER] = "Нет такой операции",
      [VA_OPERS_IN_ROW] = "Операции подряд"};
  printf("%s\n", errr_message[err]);
}