#include "s21_common.h"

#include "structs/s21_operators.h"
bool is_operation(struct operator_info o) {
  return o.o_type == O_BINARY || o.o_type == O_UNARY;
}

bool is_open_bracket(struct operator_info o) {
  return o.o_type == O_LEFT_BRACKET;
}

bool is_close_bracket(struct operator_info o) {
  return o.o_type == O_RIGHT_BRACKET;
}

bool is_operand(char c) {
  return (c >= '0' && c <= '9') || c == '.' || c == 'x';
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