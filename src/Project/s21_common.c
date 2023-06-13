#include "s21_common.h"

#include "structs/s21_operators.h"
bool is_operation(struct operator_info* o) {
  return o->o_type == O_BINARY || o->o_type == O_UNARY;
}

bool is_open_bracket(struct operator_info* o) {
  return o->o_type == O_LEFT_BRACKET;
}

bool is_close_bracket(struct operator_info* o) {
  return o->o_type == O_RIGHT_BRACKET;
}

bool is_operand(char c) {
  return (c >= '0' && c <= '9') || c == '.' || c == 'x' || c == ',';
}

void print_error(enum va_error err) {
  char* errr_message[] = {
      [VA_BRACKETS] = "неправильное количество скобок",
      [MEM_MALLOC_RES] = "проблема с памятью, лучше перезапустить",
      [VA_OK] = "Вcе ок",
      [VA_NO_OPER] = "Нет такой операции",
      [VA_OPERS_IN_ROW] = "Операции подряд",
      [CALC_STACK_UNDERFLOW] = "Не хватило операндов",
      [CALC_ERROR_NUM_INF] = "Ошибка числа",
      [CALC_ERROR] = "Не получилось посчитать",
      [MEM_MALLOC_RES_STR] = "Не удалось выделить память на строку",
      [MEM_REALLOC_RES] = "Не удалось довыделить память",
      [VA_ERROR_NUM] = "Неправильно ввели число"};
  printf("%s\n", errr_message[err]);
}
bool is_left_assoc(struct operator_info* curr) {
  return curr->assoc == ASSOC_LEFT;
}