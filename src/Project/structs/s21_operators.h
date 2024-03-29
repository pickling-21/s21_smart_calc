
#ifndef STRUCTS_S21_OPERATORS_H
#define STRUCTS_S21_OPERATORS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_structs.h"
#define QTY_OF_OPERS 20
#define ADD_OPERS 10
struct stack_operators {
  struct operator_info* data;
  size_t count;
  size_t size;
};

struct stack_ptr_operators {
  struct operator_info** data;
  size_t count;
  size_t size;
};

typedef bool find(struct operator_info*, struct operator_info*);

struct operator_info some_operator(const char* full_name, const char* nat_name,
                                   enum oper_type type, int priority,
                                   handler* func, enum assoc a);
// struct operator_info none_operator();
/*------------------*/
bool stack_operators_create(size_t size, struct stack_operators* result);
void stack_operators_destroy(struct stack_operators* s);
bool stack_operators_push(struct stack_operators* s,
                          struct operator_info value);
bool stack_operators_is_empty(const struct stack_operators* s);
bool stack_operators_is_full(const struct stack_operators* s);

/*------------------*/
bool stack_ptr_operators_create(struct stack_ptr_operators* result,
                                size_t size);
void stack_ptr_operators_destroy(struct stack_ptr_operators* s);
bool stack_ptr_operators_is_full(const struct stack_ptr_operators* s);
bool stack_ptr_operators_is_empty(const struct stack_ptr_operators* s);
bool stack_ptr_operators_push(struct stack_ptr_operators* s,
                              struct operator_info* value);
struct operator_info* stack_ptr_operators_pop(struct stack_ptr_operators* s);
struct operator_info* stack_ptr_operators_last(struct stack_ptr_operators* s);

/*------------------*/

void stack_operators_print_start(struct stack_operators* s);
// void stack_operators_print(struct stack_operators* s);
void stack_ptr_operators_print(struct stack_ptr_operators* s);

// // struct operator_info* stack_ptr_operators_find_nat_name(
// //     const struct stack_operators* haystack, const char* str_needle);
bool stack_ptr_operators_find_full_name(const struct stack_operators* haystack,
                                        const char* str_needle,
                                        struct stack_ptr_operators* st);

/*------------------*/

#endif  // STRUCTS_S21_OPERATORS_H