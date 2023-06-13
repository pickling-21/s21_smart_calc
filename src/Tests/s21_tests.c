#include <check.h>
#define X 3.14
#include "../Project/s21_calc.h"
#include "../Project/s21_common.h"
#include "../Project/s21_credit_calc.h"

//----------------------------------------------------------------------------------------------//

START_TEST(sum_1) {
  char start_string[256] = {"8903284+230"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 8903514, 7);
}
END_TEST

START_TEST(sum_2) {
  char start_string[256] = {"-1++-1"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -2, 2);
}
END_TEST

START_TEST(sum_3) {
  char start_string[256] = {"0+0"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(sum_4) {
  char start_string[256] = {"."};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_ERROR_NUM);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(sum_5) {
  char start_string[256] = {"4(84+7)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

//----------------------------------------------------------------------------------------------//

START_TEST(sub_1) {
  char start_string[256] = {"-1-----1"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -2, 7);
}
END_TEST

START_TEST(sub_2) {
  char start_string[256] = {"-1--1"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0, 7);
}
END_TEST

START_TEST(sub_3) {
  char start_string[256] = {"342-342"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(sub_4) {
  char start_string[256] = {"4394092-49348938493-823498--384398493840"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 335053125941, 7);
}
END_TEST

START_TEST(sub_5) {
  char start_string[256] = {"(838383-1232) -(299320930-1)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -298483778, 7);
}
END_TEST

//----------------------------------------------------------------------------------------------//

START_TEST(mul_1) {
  char start_string[256] = {"10*5"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 50.0, 7);
}
END_TEST

START_TEST(mul_2) {
  char start_string[256] = {"-0*459"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mul_3) {
  char start_string[256] = {"0*1023/0"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, CALC_ERROR_NUM_NAN);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mul_4) {
  char start_string[256] = {"2*2*2*8"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 64.0, 7);
}
END_TEST

START_TEST(mul_5) {
  char start_string[256] = {"-7*7"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -49.0, 7);
}
END_TEST

//----------------------------------------------------------------------------------------------//

START_TEST(div_1) {
  char start_string[256] = {"10/2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 5.0, 7);
}
END_TEST

START_TEST(div_2) {
  char start_string[256] = {"0/3423432"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(div_3) {
  char start_string[256] = {"31.349304/2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 15.674652, 7);
}
END_TEST

START_TEST(div_4) {
  char start_string[256] = {"102.3/3/2/5/5"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.682, 7);
}
END_TEST

START_TEST(div_5) {
  char start_string[256] = {"-999/0"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, CALC_ERROR_NUM_INF);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

//----------------------------------------------------------------------------------------------//

START_TEST(power_1) {
  char start_string[256] = {"10^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 100.0, 7);
}
END_TEST

START_TEST(power_2) {
  char start_string[256] = {"-12^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -144, 7);
}
END_TEST

START_TEST(power_3) {
  char start_string[256] = {"(-12)^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 144, 7);
}
END_TEST

START_TEST(power_4) {
  char start_string[256] = {"2^2^3"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 256, 7);
}
END_TEST

START_TEST(power_5) {
  char start_string[256] = {"-1^3"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -1.0, 7);
}
END_TEST

//----------------------------------------------------------------------------------------------//

START_TEST(cos_sin_1) {
  char start_string[256] = {"cos-100"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, cos(-100), 7);
}
END_TEST

START_TEST(cos_sin_2) {
  char start_string[256] = {"cos(1)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, cos(1), 7);
}
END_TEST

START_TEST(cos_sin_3) {
  char start_string[256] = {"cos-5"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, cos(-5), 7);
}
END_TEST

START_TEST(cos_sin_4) {
  char start_string[256] = {"cos(213)^2 + sin(213)^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 1.0, 7);
}
END_TEST

START_TEST(sine_1) {
  char start_string[256] = {"sin(63)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, sin(63), 7);
}
END_TEST

START_TEST(sqrt_1) {
  char start_string[256] = {"sqrt(9)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 3, 7);
}
END_TEST

START_TEST(log_1) {
  char start_string[256] = {"log(10)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, log10(10), 7);
}
END_TEST

START_TEST(ln_1) {
  char start_string[256] = {"ln(9)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, log(9), 7);
}
END_TEST

START_TEST(tan_1) {
  char start_string[256] = {"tan(9)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, tan(9), 7);
}
END_TEST

START_TEST(acos_1) {
  char start_string[256] = {"tan(1.5708)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, tan(1.5708), 7);
}
END_TEST

START_TEST(asin_1) {
  char start_string[256] = {"asin(0.5)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, asin(0.5), 7);
}
END_TEST

START_TEST(atan_1) {
  char start_string[256] = {"atan(0)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, atan(0), 7);
}
END_TEST

START_TEST(cos_sin_5) {
  char start_string[256] = {"cos1.232"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, cos(1.232), 7);
}
END_TEST

START_TEST(mix_1) {
  char start_string[256] = {"(1+2)*3+5*4"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 29.0, 7);
}
END_TEST

START_TEST(mix_2) {
  char start_string[256] = {"(((1+2)))*3"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 9.0, 7);
}
END_TEST

START_TEST(mix_3) {
  char start_string[256] = {"839*(23920+12-30-2)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 20052100, 7);
}
END_TEST

START_TEST(mix_4) {
  char start_string[256] = {"(((1*2)))-3"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -1.0, 7);
}
END_TEST

START_TEST(mix_5) {
  char start_string[256] = {"1+2+3*(0-1)+(-1)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -1.0, 7);
}
END_TEST

START_TEST(mix_6) {
  char start_string[256] = {"3+4*2/(1-5)^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 3.5, 7);
}
END_TEST

START_TEST(mix_7) {
  char start_string[256] = {"2+3^(2*1+1)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 27.0, 7);
}
END_TEST

START_TEST(mix_8) {
  char start_string[256] = {"3+5*2/(6-4)^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 5.5, 7);
}
END_TEST

START_TEST(mix_9) {
  char start_string[256] = {"3+4*2/(2+0)^(3^1)*100"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 103.0, 7);
}
END_TEST

START_TEST(mix_10) {
  char start_string[256] = {"11+(7^2)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 60.0, 7);
}
END_TEST

START_TEST(mix_11) {
  char start_string[256] = {"11+7^2"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 60.0, 7);
}
END_TEST

START_TEST(mix_12) {
  char start_string[256] = {"(0.432*54.2/4^2-(-8*4))*0.02"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.669268, 7);
}
END_TEST

START_TEST(empty) {
  char start_string[256] = {""};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_int_eq((int)result, 0);
}
END_TEST

// -----------------------------------------------
START_TEST(mix_13) {
  char start_string[256] = {"11-(123124.0001+(42-32.327)-32)*423/432"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, -120526.054910, 7);
}
END_TEST
START_TEST(mix_14) {
  char start_string[256] = {"32mod(32-30)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

//*_*_*_**_*_*_**_*_*_**_*_*_**_*_*_**_*_*_**_*_*_**_*_*_*

START_TEST(mix_15) {
  char start_string[256] = {"(1+"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_BRACKETS);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_16) {
  char start_string[256] = {"1*/+5"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OPERS_IN_ROW);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_17) {
  char start_string[256] = {"sik()1"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_NO_OPER);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_18) {
  char start_string[256] = {"4(84+1)"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, CALC_ERROR);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_19) {
  char start_string[256] = {"1/0"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, CALC_ERROR_NUM_INF);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_20) {
  char start_string[256] = {"sincossin"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, VA_OPERS_IN_ROW);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_21) {
  char start_string[256] = {"0/0"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, X, &result);
  ck_assert_int_eq(err, CALC_ERROR_NUM_NAN);
  ck_assert_double_eq_tol(result, 0.0, 7);
}
END_TEST

START_TEST(mix_22) {
  char start_string[256] = {"x+1434,23+1"};
  enum va_error err = VA_OK;
  double result = 0;
  err = s21_calc(start_string, 1.0, &result);
  ck_assert_int_eq(err, VA_OK);
  ck_assert_double_eq_tol(result, 1435.23, 7);
}
END_TEST
//----------------------------------------------------------------------------------------------//

START_TEST(credit_annuity_1) {
  size_t term = 10;
  double sum = 10000;
  double interest = 10;
  enum credit_type type = CREDIT_ANNUITY;
  struct credit_return_info result = {0};
  result.monthly_payment = malloc(sizeof(double) * term);
  credit_calc(sum, term, interest, type, &result);
  ck_assert_double_eq_tol(result.monthly_payment[0], 1046.40, 2);
  ck_assert_double_eq_tol(result.overpayment, 464.00, 2);
  ck_assert_double_eq_tol(result.psk, 10464.00, 2);
  free(result.monthly_payment);
}
END_TEST

START_TEST(credit_diff_1) {
  size_t term = 10;
  double sum = 10000;
  double interest = 10;
  enum credit_type type = CREDIT_DIFFER;
  struct credit_return_info result = {0};
  result.monthly_payment = malloc(sizeof(double) * term);
  credit_calc(sum, term, interest, type, &result);
  ck_assert_double_eq_tol(result.monthly_payment[0], 1083.33, 2);
  ck_assert_double_eq_tol(result.overpayment, 458.33, 2);
  ck_assert_double_eq_tol(result.psk, 10458.33, 2);
  free(result.monthly_payment);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int tc = 0;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, sum_1);
  tcase_add_test(tc1_1, sum_2);
  tcase_add_test(tc1_1, sum_3);
  tcase_add_test(tc1_1, sum_4);
  tcase_add_test(tc1_1, sum_5);

  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);

  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);

  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);

  tcase_add_test(tc1_1, power_1);
  tcase_add_test(tc1_1, power_2);
  tcase_add_test(tc1_1, power_3);
  tcase_add_test(tc1_1, power_4);
  tcase_add_test(tc1_1, power_5);

  tcase_add_test(tc1_1, cos_sin_1);
  tcase_add_test(tc1_1, cos_sin_2);
  tcase_add_test(tc1_1, cos_sin_3);
  tcase_add_test(tc1_1, cos_sin_4);
  tcase_add_test(tc1_1, cos_sin_5);

  tcase_add_test(tc1_1, mix_1);
  tcase_add_test(tc1_1, mix_2);
  tcase_add_test(tc1_1, mix_3);
  tcase_add_test(tc1_1, mix_4);
  tcase_add_test(tc1_1, mix_5);
  tcase_add_test(tc1_1, mix_6);
  tcase_add_test(tc1_1, mix_7);
  tcase_add_test(tc1_1, mix_8);
  tcase_add_test(tc1_1, mix_9);
  tcase_add_test(tc1_1, mix_10);
  tcase_add_test(tc1_1, mix_11);
  tcase_add_test(tc1_1, mix_12);
  tcase_add_test(tc1_1, mix_13);
  tcase_add_test(tc1_1, mix_14);
  tcase_add_test(tc1_1, mix_15);
  tcase_add_test(tc1_1, mix_16);
  tcase_add_test(tc1_1, mix_17);
  tcase_add_test(tc1_1, mix_18);
  tcase_add_test(tc1_1, mix_19);
  tcase_add_test(tc1_1, mix_20);
  tcase_add_test(tc1_1, mix_21);
  tcase_add_test(tc1_1, mix_22);

  tcase_add_test(tc1_1, sine_1);
  tcase_add_test(tc1_1, sqrt_1);
  tcase_add_test(tc1_1, tan_1);
  tcase_add_test(tc1_1, log_1);
  tcase_add_test(tc1_1, ln_1);
  tcase_add_test(tc1_1, acos_1);
  tcase_add_test(tc1_1, asin_1);
  tcase_add_test(tc1_1, atan_1);

  tcase_add_test(tc1_1, empty);

  tcase_add_test(tc1_1, credit_annuity_1);

  tcase_add_test(tc1_1, credit_diff_1);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  tc = srunner_ntests_failed(sr);
  srunner_free(sr);

  return tc == 0 ? 0 : 1;
}