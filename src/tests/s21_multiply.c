#include "test.h"

START_TEST(test_mul1) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -13204693.749302932254021561002
  s21_decimal decimal_check = {
      {0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x80150000}};
  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul2) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 13204693.749302932254021561002
  s21_decimal decimal_check = {{0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x150000}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul3) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -13204693.5
  s21_decimal decimal_check = {{0x7DEE057, 0x0, 0x0, 0x80010000}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul4) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 13204693.5
  s21_decimal decimal_check = {{0x7DEE057, 0x0, 0x0, 0x10000}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul5) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -0.9999999999999999999999999500
  s21_decimal decimal_check = {{0xFFFFE0C, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul6) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_decimal decimal_check = {{0, 0, 0, 0}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul7) {
  s21_decimal decimal1 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal decimal2 = {{1, 0, 0, 0}};
  s21_decimal decimal_check = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

START_TEST(test_mul8) {
  s21_decimal decimal1 = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal decimal2 = {{1, 0, 0, 0}};
  s21_decimal decimal_check = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};

  s21_decimal res = {{0}};
  int error = s21_mul(decimal1, decimal2, &res);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(s21_is_equal(res, decimal_check), 1);
}

Suite* create_multiply(void) {
  Suite* suite_mul = suite_create("s21_multiply");
  TCase* mul = tcase_create("case_mul");

  tcase_add_test(mul, test_mul1);
  tcase_add_test(mul, test_mul2);
  tcase_add_test(mul, test_mul3);
  tcase_add_test(mul, test_mul4);
  tcase_add_test(mul, test_mul5);
  tcase_add_test(mul, test_mul6);
  tcase_add_test(mul, test_mul7);
  tcase_add_test(mul, test_mul8);

  suite_add_tcase(suite_mul, mul);
  return suite_mul;
}