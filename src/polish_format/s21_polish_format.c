
#include "s21_polish_format.h"

#include "../s21_common.h"
#include "../structs/s21_operators.h"
enum va_error polish_format(struct stack_operators* s,
                            struct list** polish_expression, char* expression) {
  char* res_str = calloc((strlen(expression) + 1), sizeof(char));
  enum va_error error = VA_OK;
  if (res_str == NULL) error = VA_MALLOC_RES;
  if (error == VA_OK) {
    error = replace_full_name(s, expression, res_str);
    if (error == VA_OK) {
      error = validator(res_str, s);
      if (error == VA_OK) {
        *polish_expression = inf_to_post(res_str, s);
      }
    }
  }
  printf("POLISH FORMAT\n");
  *polish_expression != NULL ? list_print(*polish_expression)
                             : printf("IS NULL\n");
  print_error(error);
  if (error != VA_MALLOC_RES) free(res_str);
  return error;
}
