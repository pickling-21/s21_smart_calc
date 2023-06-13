#include "../s21_common.h"
#include "s21_polish_format.h"

enum va_error replace_full_name(const struct stack_operators* opers,
                                const char* str, struct list** list_res,
                                double x) {
  enum va_error err = VA_OK;
  bool may_unary = true;

  while (*str != '\0' && err == VA_OK) {
    if (is_operand(*str)) {
      err = add_number(list_res, &str, x) ? VA_OK : VA_ERROR_NUM;
      may_unary = false;
    } else {
      err = find_and_add_operation_to_list(opers, &str, list_res, &may_unary);
    }
  }
  return err;
}

enum va_error find_and_add_operation_to_list(
    const struct stack_operators* opers, const char** str,
    struct list** list_res, bool* may_unary) {
  enum va_error err = VA_OK;
  struct stack_ptr_operators stack = {0};
  struct stack_ptr_operators* curr_oper_stack = &stack;

  if (stack_ptr_operators_create(curr_oper_stack, QTY_OF_OPERS) &&
      stack_ptr_operators_find_full_name(opers, *str, curr_oper_stack)) {
    if (!stack_ptr_operators_is_empty(curr_oper_stack)) {
      struct operator_info* a = curr_oper_stack->data[0];
      if (curr_oper_stack->count == 1) {
        replace_one(curr_oper_stack->data[0], may_unary);
      } else {
        replace_unary_clones(curr_oper_stack, may_unary, &a);
      }
      list_add_back_operation(list_res, a);
      *str += strlen(a->full_name);
    } else {
      err = VA_NO_OPER;
    }
    stack_ptr_operators_destroy(curr_oper_stack);
  } else {
    err = MEM_MALLOC_RES;
  }
  return err;
}

bool unary_or_binanry_two(struct operator_info* curr,
                          struct operator_info* next) {
  return (curr->o_type == O_BINARY && next->o_type == O_UNARY) ||
         (curr->o_type == O_UNARY && next->o_type == O_BINARY);
}

struct operator_info* unary_from_two(struct operator_info* curr,
                                     struct operator_info* next) {
  return curr->o_type == O_UNARY ? curr : next;
}

struct operator_info* binary_from_two(struct operator_info* curr,
                                      struct operator_info* next) {
  return curr->o_type == O_BINARY ? curr : next;
}

void replace_one(const struct operator_info* o, bool* may_unary) {
  if (o->o_type == O_RIGHT_BRACKET)
    *may_unary = false;
  else
    *may_unary = true;
}

void replace_unary_clones(const struct stack_ptr_operators* fr, bool* may_unary,
                          struct operator_info** finded) {
  for (size_t j = 0; j < fr->count - 1; j++) {
    struct operator_info* a = fr->data[j];
    struct operator_info* b = fr->data[j + 1];
    if (unary_or_binanry_two(a, b)) {
      *finded = unary_from_two(a, b);
      if (!*may_unary) {
        *finded = binary_from_two(a, b);
      }
    }
  }
  *may_unary = true;
}

bool add_number(struct list** l, char const** str, double x) {
  bool result = true;
  char* end_number = NULL;
  if (**str != 'x') {
    double number = strtod(*str, &end_number);
    if (end_number == *str) end_number = NULL;
    list_add_back_num(l, number);
    if (end_number == NULL) result = false;
  } else {
    list_add_back_num(l, x);
  }
  *str = (end_number != NULL) ? end_number : *str + 1;
  return result;
}
