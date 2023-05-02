#ifndef STRUCTS_S21_QUEUE_H
#define STRUCTS_S21_QUEUE_H

#include "s21_operators.h"

struct queue {
  struct list *front, *rear;
};
#endif  // STRUCTS_S21_QUEUE_H
