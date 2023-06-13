#ifndef S21_CREDIT_CALC_H
#define S21_CREDIT_CALC_H
#include <math.h>
#include <stdbool.h>
#include <string.h>
struct credit_return_info {
  double* monthly_payment;
  double overpayment;
  double psk;
};

enum credit_type { CREDIT_ANNUITY, CREDIT_DIFFER };

enum term_type { MONTH, YEAR };

void credit_calc(double sum, size_t term, double interest,
                 enum credit_type type, struct credit_return_info* result);

#endif  // S21_CREDIT_CALC_H
