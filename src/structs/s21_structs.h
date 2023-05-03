#ifndef STRUCTS_S21_STRUCTS_H
#define STRUCTS_S21_STRUCTS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct maybe_num(handler)(double* items);

enum oper_type {
  O_NO_TYPE,
  O_UNARY,
  O_BINARY,
  O_LEFT_BRACKET,
  O_RIGHT_BRACKET
};

struct operator_info {
  char* full_name;
  char* nat_name;
  enum oper_type o_type;
  uint16_t priority;
  handler* func;
};

enum l_type { L_NO_TYPE, L_NUMBER, L_X, L_OPERATOR };

struct lexeme {
  enum l_type type;
  double number;
  struct operator_info oper;
};

enum valid_num { M_N_OK, M_N_NAN, M_N_INF };

struct maybe_num {
  double value;
  enum valid_num valid;
};

#endif  // STRUCTS_S21_STRUCTS_H