#include "s21_list.h"

#include "s21_operators.h"
#include "s21_structs.h"

static struct lexeme some_oper(struct operator_info *o) {
  return (struct lexeme){.type = L_OPERATOR, .oper = o, .number = 0};
}

static struct lexeme some_num(double n) {
  return (struct lexeme){.type = L_NUMBER, .oper = NULL, .number = n};
}

// static struct lexeme none_lexeme() {
//   return (struct lexeme){.type = L_NO_TYPE, .oper = NULL, .number = 0};
// }

struct list *node_create(struct lexeme value) {
  struct list *list = malloc(sizeof(struct list));
  if (list) {
    list->value = value;
    list->next = NULL;
  }
  return list;
}

void list_destroy(struct list *list) {
  while (list) {
    struct list *temp = list;
    list = list->next;
    free(temp);
  }
}

void list_add_front(struct list **old, struct lexeme value) {
  struct list *new = node_create(value);
  if (old != NULL) {
    new->next = *old;
    *old = new;
  }
}

void list_add_back_num(struct list **old, double num) {
  list_add_back(old, some_num(num));
}

bool list_add_back_operation(struct list **l, struct operator_info *o) {
  bool result = false;
  if (o != NULL) {
    list_add_back(l, some_oper(o));
    result = true;
  }
  return result;
}

void list_add_back(struct list **old, struct lexeme value) {
  if (*old != NULL) {
    list_last(*old)->next = node_create(value);
  } else {
    list_add_front(old, value);
  }
}

struct list *list_last(struct list *list) {
  while (list && list->next) {
    list = list->next;
  }
  return list;
}

// size_t list_length(struct list const *list) {
//   size_t len = 0;
//   struct list *tmp = (struct list *)list;
//   for (; tmp; len++, tmp = tmp->next)
//     ;
//   return len;
// }

void list_foreach(struct list const *l, void(f)(struct lexeme)) {
  while (l) {
    f(l->value);
    l = l->next;
  }
}

// struct lexeme list_pop_front(struct list **l) {
//   struct lexeme res = none_lexeme();
//   if (*l == NULL) {
//     printf("\nQueue Underflow");
//   } else {
//     struct list *tmp = *l;
//     res = tmp->value;
//     *l = (*l)->next;
//     // if (tmp)
//     free(tmp);
//   }
//   return res;
// }

// bool list_is_empty(struct list *l) { return l == NULL; };

/*----------------*/
// static void print_int64_space(double i) {
//   printf("%.1lf", i);
//   printf(" ");
// }

// static void print_operator(struct operator_info *o) {
//   printf("%s ", o->nat_name);
// }

// void print_lexeme(struct lexeme val) {
//   if (val.type == L_NUMBER) {
//     print_int64_space(val.number);
//   } else if (val.type == L_OPERATOR) {
//     print_operator(val.oper);
//   } else if (val.type == L_NO_TYPE) {
//     printf("no ");
//   }
// }
// /*----------------*/

// void list_print(struct list const *l) { list_foreach(l, print_lexeme); };

bool last_from_stack_to_list(struct list *l, struct stack_ptr_operators *s) {
  bool result = false;
  struct operator_info *o = stack_ptr_operators_pop(s);
  list_add_back_operation(&l, o);
  return result;
}
