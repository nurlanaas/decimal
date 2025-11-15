#include "test.h"

START_TEST(less_1) {
  s21_decimal a = {{0, 0, 3, 0}};
  s21_decimal b = {{0, 0, 3, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(less_2) {
  s21_decimal a = {{4567, 0, 0, 0}};
  s21_decimal b = {{12, 0, 0, 0}};
  s21_set_scale(&a, 12);

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_3) {
  s21_decimal a = {{4567, 0, 0, 0}};
  s21_decimal b = {{12, 0, 345699, 0}};
  s21_set_scale(&b, 12);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(less_4) {
  s21_decimal a = {{4567, 345678, 4567, 0}};
  s21_decimal b = {{12, 45678, 23456, 0}};
  s21_set_scale(&a, 12);
  s21_set_sign(&b, 0);

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_5) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{145654, 68, 0, 0}};
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(less_6) {
  s21_decimal a = {{4567890, 0, 0, 0}};
  s21_decimal b = {{0, 68, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_7) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(less_8) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 68, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_9) {
  s21_decimal a = {{4567890, 0, 0, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_10) {
  s21_decimal a = {{4567890, 56321, 84515, 0}};
  s21_decimal b = {{7890, 56321, 84515, 0}};
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(less_11) {
  s21_decimal a = {{7890, 56321, 84515, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{4567890, 56321, 84515, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_12) {
  s21_decimal a = {{4567890, 874848, 488446, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{465156, 464, 844, 0}};
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_13) {
  s21_decimal a = {{4567890, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(less_or_equal_1) {
  s21_decimal a = {{0, 0, 3, 0}};
  s21_decimal b = {{0, 0, 3, 0}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST
START_TEST(less_or_equal_2) {
  s21_decimal a = {{0, 0, 3, 0}};
  s21_decimal b = {{8546, 8465486, 3, 0}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(greater_1) {
  s21_decimal a = {{0, 0, 3, 0}};
  s21_decimal b = {{0, 0, 3, 0}};

  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(greater_2) {
  s21_decimal a = {{4567, 0, 0, 0}};
  s21_decimal b = {{12, 0, 0, 0}};
  s21_set_scale(&a, 12);

  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(greater_3) {
  s21_decimal a = {{4567, 0, 0, 0}};
  s21_decimal b = {{12, 0, 345699, 0}};
  s21_set_scale(&b, 12);
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(greater_4) {
  s21_decimal a = {{4567, 345678, 4567, 0}};
  s21_decimal b = {{12, 45678, 23456, 0}};
  s21_set_scale(&a, 12);
  s21_set_sign(&b, 0);

  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(greater_5) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{145654, 68, 0, 0}};
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(greater_or_equal_1) {
  s21_decimal a = {{61818, 566581, 3, 0}};
  s21_decimal b = {{0, 69526, 3, 0}};

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(greater_or_equal_2) {
  s21_decimal a = {{0, 0, 3, 0}};
  s21_decimal b = {{0, 0, 3, 0}};

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(greater_or_equal_3) {
  s21_decimal a = {{61818, 5661, 3, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{0, 69526, 3, 0}};

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST

START_TEST(equal_1) {
  s21_decimal a = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal b = {{MAX4BITE - 1, MAX4BITE, MAX4BITE, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(equal_2) {
  s21_decimal a = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal b = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(not_equal_1) {
  s21_decimal a = {{555, 555, 555, 0}};
  s21_decimal b = {{MAX4BITE - 1, MAX4BITE, MAX4BITE, 0}};

  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(not_equal_2) {
  s21_decimal a = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};
  s21_decimal b = {{MAX4BITE, MAX4BITE, MAX4BITE, 0}};

  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

Suite *create_compare(void) {
  Suite *suite_compare = suite_create("compare");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_less = tcase_create("less");
  TCase *tcase_less_or_equal = tcase_create("less_or_equal");
  TCase *tcase_greater = tcase_create("greater");
  TCase *tcase_greater_or_equal = tcase_create("greater_or_equal");
  TCase *tcase_equal = tcase_create("equal");
  TCase *tcase_not_equal = tcase_create("not_equal");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_less, less_1);  // тесты на less
  tcase_add_test(tcase_less, less_2);
  tcase_add_test(tcase_less, less_3);
  tcase_add_test(tcase_less, less_4);
  tcase_add_test(tcase_less, less_5);
  tcase_add_test(tcase_less, less_6);
  tcase_add_test(tcase_less, less_7);
  tcase_add_test(tcase_less, less_8);
  tcase_add_test(tcase_less, less_9);
  tcase_add_test(tcase_less, less_10);
  tcase_add_test(tcase_less, less_11);
  tcase_add_test(tcase_less, less_12);
  tcase_add_test(tcase_less, less_13);

  tcase_add_test(tcase_less, less_or_equal_1);
  tcase_add_test(tcase_less, less_or_equal_2);

  tcase_add_test(tcase_greater, greater_1);
  tcase_add_test(tcase_greater, greater_2);
  tcase_add_test(tcase_greater, greater_3);
  tcase_add_test(tcase_greater, greater_4);
  tcase_add_test(tcase_greater, greater_5);

  tcase_add_test(tcase_greater_or_equal, greater_or_equal_1);
  tcase_add_test(tcase_greater_or_equal, greater_or_equal_2);
  tcase_add_test(tcase_greater_or_equal, greater_or_equal_3);

  tcase_add_test(tcase_equal, equal_1);
  tcase_add_test(tcase_equal, equal_2);

  tcase_add_test(tcase_not_equal, not_equal_1);
  tcase_add_test(tcase_not_equal, not_equal_2);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite_compare, tcase_less);
  suite_add_tcase(suite_compare, tcase_less_or_equal);
  suite_add_tcase(suite_compare, tcase_greater);
  suite_add_tcase(suite_compare, tcase_greater_or_equal);
  suite_add_tcase(suite_compare, tcase_equal);
  suite_add_tcase(suite_compare, tcase_not_equal);

  return suite_compare;
}