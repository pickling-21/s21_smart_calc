#ifndef S21_CALC_H
#define S21_CALC_H
#include "polish_format/s21_polish_format.h"
#include "s21_common.h"
#include "structs/s21_operators.h"
void oper_push(struct stack_operators* s);
enum va_error s21_calc(const char* str, double x, double* res);
#endif  // S21_CALC_H
