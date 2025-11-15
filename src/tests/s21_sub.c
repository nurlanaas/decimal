#include "test.h"

START_TEST(sub_1) {
  s21_decimal a = {{0, 60, 80, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{0, 600, 0, 0}};
  s21_set_sign(&b, 1);
  s21_decimal result = {0};
  int error = s21_sub(a, b, &result);
  long double d_result = s21_to_ldouble(result);
  long double d_a = s21_to_ldouble(a);
  long double d_b = s21_to_ldouble(b);

  ck_assert_ldouble_eq(d_result, d_a - d_b);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal a = {{100, 6789, 56789, 0}};
  s21_decimal b = {{0}};
  s21_decimal res = {{0}};
  s21_decimal res_eq = {{100, 6789, 56789, 0}};

  int error = s21_sub(a, b, &res);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal a = {{12345, 0, 0, 0}};  // 123.45
  s21_set_scale(&a, 2);
  s21_decimal b = {{123, 0, 0, 0}};  // 123
  s21_decimal res = {{0}};
  s21_decimal expected = {{45, 0, 0, 0}};  // 0.45
  s21_set_scale(&expected, 2);

  int error = s21_sub(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal a = {
      {MAX4BITE, MAX4BITE, MAX4BITE, 0}};  // Максимальное положительное число
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_sign(&b, 1);
  s21_decimal res = {{0}};

  int error = s21_sub(a, b, &res);
  ck_assert_int_eq(error,
                   1);  // переполнение: MAX_DECIMAL - (-1) = MAX + 1 → overflow
}
END_TEST

START_TEST(sub_5) {
  s21_decimal a = {
      {MAX4BITE, MAX4BITE, MAX4BITE, 0}};  // Минимальное отрицательное число
  s21_set_sign(&a, 1);
  s21_decimal b = {{1, 0, 0, 0}};  // -1
  s21_decimal res = {{0}};

  int error = s21_sub(a, b, &res);
  ck_assert_int_eq(error, 2);  // переполнение: MIN_DECIMAL - 1 → overflow
}
END_TEST

START_TEST(sub_6) {
  s21_decimal a = {{1, 0, 0, 0}};  // 0.000001
  s21_set_scale(&a, 6);
  s21_decimal b = {{1, 0, 0, 0}};  // 1
  s21_decimal res = {{0}};
  s21_decimal expected = {{999999, 0, 0, 0}};
  s21_set_scale(&expected, 6);
  s21_set_sign(&expected, 1);  // -0.999999

  int error = s21_sub(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

Suite *create_sub(void) {
  Suite *suite_sub = suite_create("sub");

  TCase *sub = tcase_create("sub");
  tcase_add_test(sub, sub_1);
  tcase_add_test(sub, sub_2);
  tcase_add_test(sub, sub_3);
  tcase_add_test(sub, sub_4);
  tcase_add_test(sub, sub_5);
  tcase_add_test(sub, sub_6);

  suite_add_tcase(suite_sub, sub);

  return suite_sub;
}