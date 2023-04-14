#include "../s21_common.h"
#include "s21_polish_format.h"

enum va_error replace_full_name(const struct stack_operators* opers,
                                const char* str, char* result) {
  enum va_error err = VA_OK;
  bool may_unary = true;
  for (size_t curr = 0; *str != '\0' && err == VA_OK; curr++) {
    if (!is_operand(*str) && !is_space(*str)) {
      struct stack_operators curr_oper_stack =
          stack_operators_find_full_name(opers, str);

      if (stack_operators_is_empty(&curr_oper_stack)) err = VA_NO_OPER;
      if (err == VA_OK && curr_oper_stack.count > 0) {
        char* nat_name = curr_oper_stack.data[0].nat_name;
        if (curr_oper_stack.count == 1) {
          replace_one(curr_oper_stack.data[0], &may_unary);
        } else {
          replace_unary_clones(&curr_oper_stack, &may_unary, curr, &nat_name);
        }
        replace_and_write(&str, &result, curr_oper_stack.data[0].full_name,
                          nat_name);
        stack_operators_destroy(&curr_oper_stack);
      }

    } else {
      if (is_space(*str)) {
        str++;
      } else {
        // операнд
        may_unary = false;
        *result++ = *str++;
      }
    }
    printf("str now %s\n", str + curr);
  }
  *result = '\0';
  return err;
}

bool is_space(const char sym) { return sym == ' '; }

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
  return curr.o_type == O_BINARY ? curr : next;
}

void replace_one(const struct operator_info o, bool* may_unary) {
  if (o.o_type == O_RIGHT_BRACKET)
    *may_unary = false;
  else
    *may_unary = true;
}

void replace_unary_clones(const struct stack_operators* fr, bool* may_unary,
                          const size_t curr, char** nat_name) {
  for (size_t j = 0; j < fr->count - 1; j++) {
    struct operator_info a = fr->data[j];
    struct operator_info b = fr->data[j + 1];
    if (unary_or_binanry_two(a, b)) {
      *nat_name = unary_from_two(a, b).nat_name;
      if (!*may_unary) {
        *nat_name = binary_from_two(a, b).nat_name;
      }
    }
  }
}