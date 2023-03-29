
#include "s21_notation.h"
#include "s21_stek_queue.h"

int main() {
  struct list *a = inf_to_post();
  list_foreach(a, print_int64_space);
  return 0;
}