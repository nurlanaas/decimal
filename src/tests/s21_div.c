#include "test.h"

START_TEST(div_1) {
  s21_decimal a = {{0b01001010000000111000000000000000,
                    0b00000000010011101101111011001000, 0, 0}};
  // 22200000000000000
  s21_decimal b = {{0b00000000000000000010011100010000, 0, 0, 0}};
  // 10000
  s21_decimal res = {0};
  s21_decimal res_eq = {{0b11100010010011111011100000000000,
                         0b00000000000000000000001000000100, 0, 0}};
  // 2220000000000
  int error = s21_div(a, b, &res);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

START_TEST(div_2) {
  s21_decimal a = {{100, 0, 0, 0}};  // 100
  s21_decimal b = {{0}};             // 0
  s21_decimal res = {{0}};

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 3);  // ошибка деление на ноль
}
END_TEST

START_TEST(div_3) {
  s21_decimal a = {{0}};             // 0
  s21_decimal b = {{500, 0, 0, 0}};  // 500
  s21_decimal res = {{0}};
  s21_decimal res_eq = {{0}};  // 0

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

START_TEST(div_4) {
  s21_decimal a = {{1000000, 0, 0, 0}};  // 1000000
  s21_decimal b = {{1000000, 0, 0, 0}};  // 1000000
  s21_decimal res = {{0}};
  s21_decimal res_eq = {{1, 0, 0, 0}};  // 1

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

START_TEST(div_5) {
  s21_decimal a = {{1000000, 0, 0, 0}};  // -1000000
  s21_set_sign(&a, 1);
  s21_decimal b = {{2000, 0, 0, 0}};  // -2000
  s21_set_sign(&b, 1);
  s21_decimal res = {{0}};
  s21_decimal res_eq = {{500, 0, 0, 0}};  // 500

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

START_TEST(div_6) {
  s21_decimal a = {{1000000, 0, 0, 0}};  // -1000000
  s21_set_sign(&a, 1);
  s21_decimal b = {{20000, 0, 0, 0}};  // 2000
  s21_set_scale(&b, 1);
  s21_decimal res = {{0}};
  s21_decimal res_eq = {{500, 0, 0, 0}};  // -500
  s21_set_sign(&res_eq, 1);

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

START_TEST(div_7) {
  s21_decimal a = {{1000001, 0, 0, 0}};  // 1000001
  s21_decimal b = {{1000000, 0, 0, 0}};  // 1000000
  s21_decimal res = {{0}};
  s21_decimal res_eq = {
      {0b00000000000011110100001001000001, 0, 0, 0}};  // 1.00001
  s21_set_scale(&res_eq, 6);
  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

START_TEST(div_8) {
  s21_decimal a = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res = {0};

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 1);  // Overflow
}
END_TEST

START_TEST(div_9) {
  s21_decimal a = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res = {0};

  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 2);  // Overflow
}
END_TEST

START_TEST(div_10) {
  s21_decimal a = {{100000100, 0, 0, 0}};  // 1000001.00
  s21_set_scale(&a, 2);
  s21_decimal b = {{1000000, 0, 0, 0}};  // 1000000
  s21_decimal res = {{0}};
  s21_decimal res_eq = {
      {0b00000000000011110100001001000001, 0, 0, 0}};  // 1.00001
  s21_set_scale(&res_eq, 6);
  int error = s21_div(a, b, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(s21_is_equal(res, res_eq), 1);
}
END_TEST

Suite *create_div(void) {
  Suite *suite_division = suite_create("division");

  TCase *division = tcase_create("div");
  tcase_add_test(division, div_1);
  tcase_add_test(division, div_2);
  tcase_add_test(division, div_3);
  tcase_add_test(division, div_4);
  tcase_add_test(division, div_5);
  tcase_add_test(division, div_6);
  tcase_add_test(division, div_7);
  tcase_add_test(division, div_8);
  tcase_add_test(division, div_9);
  tcase_add_test(division, div_10);

  suite_add_tcase(suite_division, division);

  return suite_division;
}