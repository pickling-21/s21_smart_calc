
#include "s21_polish_format.h"

#include "../s21_common.h"
#include "../structs/s21_operators.h"
enum va_error polish_format(const struct stack_operators* opers,
                            struct list** polish_expression,
                            const char* expression, double x) {
  char* res_str = NULL;
  enum va_error error = VA_OK;
  res_str = calloc((strlen(expression) + 1), sizeof(char));
  if (res_str != NULL) {
    remove_unnecessary(expression, res_str);
    struct list* inf_expression = NULL;
    error = replace_full_name(opers, res_str, &inf_expression, x);
    if (error == VA_OK) error = validator(inf_expression);
    if (error == VA_OK) error = inf_to_post(inf_expression, polish_expression);
    if (inf_expression != NULL) list_destroy(inf_expression);
    free(res_str);
  } else
    error = MEM_MALLOC_RES_STR;
  return error;
}

void remove_unnecessary(const char* expression, char* result) {
  for (; *expression != '\0';) {
    if (is_space(*expression)) {
      expression++;
    } else if (*expression == ',') {
      *result++ = '.';
      expression++;
    } else {
      *result++ = *expression++;
    }
  }
}

bool is_space(const char sym) { return sym == ' '; }