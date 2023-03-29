
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stek_queue.h"

bool is_digit(char c) { return (c >= '0' && c <= '9'); }

struct list *inf_to_post() {
  struct list *a = NULL;
  char *str = "123.432 + 1";
  char *tmp = str;
  char *end = NULL;
  // char sign = 0;
  while (*tmp != '\0') {
    if (is_digit(*tmp)) {
      double number = strtod(tmp, &end);
      list_add_back(&a, (struct symbols){.type = number, .number = number});
      tmp = end;
    } else {
      // sign and other implementation
      tmp++;
    }
  }
  printf("%s", end);
  return a;
};
