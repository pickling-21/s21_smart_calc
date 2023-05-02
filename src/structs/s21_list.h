#ifndef STRUCTS_S21_LIST_H
#define STRUCTS_S21_LIST_H

#include "s21_operators.h"

enum l_type { L_NO_TYPE, L_NUMBER, L_X, L_OPERATOR };

struct lexeme {
  enum l_type type;
  double number;
  struct operator_info oper;
};

struct list {
  struct lexeme value;
  struct list *next;
};

struct list *node_create(struct lexeme value);

struct lexeme list_pop_first(struct list *old);
void list_add_front(struct list **old, struct lexeme value);
void list_add_back(struct list **old, struct lexeme value);
void list_add_back_num(struct list **old, double num);
void list_add_back_x(struct list **old);
// // добавляем в начало списка
size_t list_length(struct list const *list);
void list_destroy(struct list *list);
struct list *list_last(struct list *const list);
void list_foreach(struct list const *l, void(f)(struct lexeme));
void list_print(struct list const *l);
bool last_from_stack_to_list(struct list *l, struct stack_operators *s);
struct lexeme list_pop_front(struct list **l);
void print_lexeme(struct lexeme val);

#endif  // STRUCTS_S21_LIST_H