#include "test.h"

START_TEST(other_floor_1) {
  s21_decimal a = {{3123, 0, 0, 0}};
  s21_set_scale(&a, 1);
  int error = s21_floor(a, &a);
  s21_decimal exp_a = {{312, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, exp_a), 1);
  ck_assert_int_eq(error, 0);

  s21_decimal b = {{3123, 0, 0, 0}};
  s21_set_scale(&b, 1);
  s21_set_sign(&b, 1);
  int error1 = s21_floor(b, &b);
  s21_decimal exp_b = {{313, 0, 0, 0}};  // -312.3 -> -313
  s21_set_sign(&exp_b, 1);
  ck_assert_int_eq(s21_is_equal(b, exp_b), 1);
  ck_assert_int_eq(error1, 0);
}
END_TEST

START_TEST(other_floor_2) {
  s21_decimal a = {{3123, 0, 0, 0}};
  s21_set_sign(&a, 1);
  int error = s21_floor(a, &a);
  s21_decimal exp_a = {{3123, 0, 0, 0}};
  s21_set_sign(&exp_a, 1);
  ck_assert_int_eq(s21_is_equal(a, exp_a), 1);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(other_round_1) {
  s21_decimal a = {{3123, 0, 0, 0}};  // 312.3
  s21_set_scale(&a, 1);
  int error = s21_round(a, &a);
  s21_decimal exp_a = {{312, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, exp_a), 1);
  ck_assert_int_eq(error, 0);

  s21_decimal b = {{3125, 0, 0, 0}};
  s21_set_scale(&b, 1);
  s21_set_sign(&b, 1);
  int error1 = s21_round(b, &b);
  s21_decimal exp_b = {{313, 0, 0, 0}};  // -312.5 -> -313
  s21_set_sign(&exp_b, 1);
  ck_assert_int_eq(s21_is_equal(b, exp_b), 1);
  ck_assert_int_eq(error1, 0);
}
END_TEST

START_TEST(other_round_2) {
  s21_decimal a = {{90, 50, 111, 0}};  // 312.3
  int error = s21_round(a, &a);
  s21_decimal exp_a = {{90, 50, 111, 0}};
  ck_assert_int_eq(s21_is_equal(a, exp_a), 1);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(other_truncate_1) {
  s21_decimal a = {{3723, 0, 0, 0}};  // 312.3
  s21_set_scale(&a, 3);
  int error = s21_truncate(a, &a);
  s21_decimal exp_a = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, exp_a), 1);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(other_truncate_2) {
  s21_decimal b = {{3125, 0, 0, 0}};
  s21_set_sign(&b, 1);
  int error1 = s21_truncate(b, &b);
  s21_decimal exp_b = {{3125, 0, 0, 0}};  // -312.5 -> -313
  s21_set_sign(&exp_b, 1);
  ck_assert_int_eq(s21_is_equal(b, exp_b), 1);
  ck_assert_int_eq(error1, 0);
}
END_TEST

START_TEST(other_negate_1) {
  s21_decimal b = {{3125, 0, 0, 0}};
  s21_set_sign(&b, 1);
  int error1 = s21_negate(b, &b);
  s21_decimal exp_b = {{3125, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(b, exp_b), 1);
  ck_assert_int_eq(error1, 0);
}
END_TEST

Suite *create_other(void) {
  Suite *suite_other = suite_create("other");

  TCase *floor = tcase_create("floor");
  tcase_add_test(floor, other_floor_1);
  tcase_add_test(floor, other_floor_2);

  TCase *round = tcase_create("round");
  tcase_add_test(round, other_round_1);
  tcase_add_test(round, other_round_2);

  TCase *truncate = tcase_create("truncate");
  tcase_add_test(truncate, other_truncate_1);
  tcase_add_test(truncate, other_truncate_2);

  TCase *negate = tcase_create("negate");
  tcase_add_test(negate, other_negate_1);

  suite_add_tcase(suite_other, floor);
  suite_add_tcase(suite_other, round);
  suite_add_tcase(suite_other, truncate);
  suite_add_tcase(suite_other, negate);

  return suite_other;
}