#ifndef S21_STEK_QUEUE_H
#define S21_STEK_QUEUE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*---------------------*/

/* list(queune)*/

struct maybe_num {
  double value;
  bool valid;
};

enum type { NO_TYPE, NUMBER, OPERATION };

enum oper_category {
  NONE,
  SIN,
  COS,
  LEFT,
  RIGHT,
  PLUS,
  MINUS,
  MUL,
  DIV,
  MOD,
  POWER,
};

struct symbols {
  enum type type;
  double number;
  enum oper_category operator;
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

struct stack_operators {
  size_t count;
  enum oper_category *data;
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

struct symbols some_oper(enum oper_category o);
struct symbols some_number(double i);

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
  struct stack_operators_interface {
    struct stack_operators (*create)(size_t);
    bool (*empty)(struct stack_operators const *);
    bool (*full)(struct stack_operators const *);
    void (*destroy)(struct stack_operators *);
    bool (*push)(struct stack_operators *, enum oper_category);
    enum oper_category (*pop)(struct stack_operators *);
    enum oper_category (*last)(struct stack_operators *);
    void (*print)(struct stack_operators *);
  } opers_st;
};

/*char stack*/
struct stack_operators stack_operators_create(size_t size);
void stack_operators_destroy(struct stack_operators *s);
bool stack_operators_push(struct stack_operators *s, enum oper_category value);
enum oper_category stack_operators_pop(struct stack_operators *s);
bool stack_operators_is_empty(const struct stack_operators *s);
bool stack_operators_is_full(const struct stack_operators *s);
enum oper_category stack_operators_last(struct stack_operators *s);
void stack_operators_print(struct stack_operators *s);

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
void print_symbols(struct symbols i);

struct list *node_create(struct symbols value);
void list_add_front(struct list **old, struct symbols value);
// добавляем в начало списка
size_t list_length(struct list const *const list);
void list_destroy(struct list *list);
struct list *list_last(struct list *list);
void list_add_back(struct list **old, struct symbols value);
void list_foreach(struct list const *l, void(f)(struct symbols));
bool last_from_stack_to_list(struct list *l, struct stack_operators *s);
/*---------------------*/

#endif  // S21_STEK_QUEUE_H