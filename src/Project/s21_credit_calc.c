#include "s21_credit_calc.h"

void credit_calc(double sum, size_t term, double interest,
                 enum credit_type type, struct credit_return_info* result) {
  double p = interest / 100 / 12;

  if (type == CREDIT_ANNUITY) {
    result->monthly_payment[0] = sum * (p + (p / ((pow(1 + p, term) - 1))));
    result->overpayment = result->monthly_payment[0] * term - sum;
    result->psk = sum + result->overpayment;

  } else if (type == CREDIT_DIFFER) {
    double debt_part = sum / term;  // сумма платежа по основному долгу
    double loan_balance = sum;
    double interest_part = loan_balance * p;  // процентная часть
    for (size_t i = 0; i < term; i++) {
      interest_part = loan_balance * p;
      result->monthly_payment[i] = debt_part + interest_part;
      result->psk += result->monthly_payment[i];
      loan_balance -= debt_part;
    }
    result->overpayment = result->psk - sum;
  }
}
