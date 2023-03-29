#ifndef S21_STEK_QUEUE_H
#define S21_STEK_QUEUE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* num */
struct maybe_num {
  double value;
  bool valid;
};

struct maybe_sign {
  char value;
  bool valid;
};

/*---------------------*/

/* list(queune)*/

enum type {
  number,
  operation,
};

enum priorities {
  hello,
};

enum operations {
  o_add,
  o_sub,
  o_mul,
  o_div,
};

struct operation {
  enum operations oper;
  enum priorities priority;
};

struct symbols {
  enum type type;
  double number;
  struct operation operation;
};

struct list {
  struct symbols value;
  struct list *next;
};

struct stack_double {
  size_t count;
  double *data;
  size_t size;
};

struct stack_char {
  size_t count;
  double *data;
  size_t size;
};

/* нужно для стек double??? */
enum stack_result {
  STACK_OK,
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
};
/*----------------*/
enum ins_arg_type { IAT_NOARG, IAT_I64 };

struct ins_descr {
  enum ins_arg_type argtype;  // тип аргументов: 0, 1 численных аргументов
  size_t stack_min;  // минимальное количество элементов для инструкции
  int64_t stack_delta;  // сколько требуется аргументов в стеке
};
/* --------------*/

// добавить возврат enum у функций?
struct stack_interface {
  struct stack_double_interface {
    struct stack_double (*create)(size_t);
    bool (*empty)(struct stack_double const *);
    bool (*full)(struct stack_double const *);
    void (*destroy)(struct stack_double *);
    bool (*push)(struct stack_double *, double);
    struct maybe_num (*pop)(struct stack_double *);
  } double_st;
  struct stack_char_interface {
    struct stack_char (*create)(size_t);
    bool (*empty)(struct stack_char const *);
    bool (*full)(struct stack_char const *);
    void (*destroy)(struct stack_char *);
    bool (*push)(struct stack_char *, double);
    struct maybe_sign (*pop)(struct stack_char *);
  } char_st;
};

/*char stack*/
struct stack_char stack_char_create(size_t size);
void stack_char_destroy(struct stack_char *s);
bool stack_char_push(struct stack_char *s, double value);
struct maybe_sign stack_char_pop(struct stack_char *s);
bool stack_char_is_empty(const struct stack_char *s);
bool stack_char_is_full(const struct stack_char *s);

/*double stack*/
// добавить функции арифметики (для чтения постфиксной нотации)
struct stack_double stack_double_create(size_t size);
void stack_double_destroy(struct stack_double *s);
bool stack_double_push(struct stack_double *s, double value);
struct maybe_num stack_double_pop(struct stack_double *s);
bool stack_double_is_empty(const struct stack_double *s);
bool stack_double_is_full(const struct stack_double *s);

/*---------------------------*/

void print_int64_space(double i);

struct list *node_create(struct symbols value);
void list_add_front(struct list **old, struct symbols value);
// добавляем в начало списка
size_t list_length(struct list const *const list);
void list_destroy(struct list *list);
struct list *list_last(struct list *list);
void list_add_back(struct list **old, struct symbols value);
void list_foreach(struct list const *l, void(f)(double));

/*---------------------*/

#endif  // S21_STEK_QUEUE_H