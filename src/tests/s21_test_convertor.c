#include "test.h"

START_TEST(from_dec_to_int_1) {
  s21_decimal a = {{3123, 1234, 0, 0}};
  int ans = 0;
  int error = s21_from_decimal_to_int(a, &ans);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(from_float_to_deс_1) {
  float a = 1e-29;
  s21_decimal b = {{3123, 0, 0, 0}};
  int error = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(from_float_to_deс_2) {  /// ????
  float a = MAX_DECIMAL + 12312342232432323134232.2;
  s21_decimal b = {{3123, 0, 0, 0}};
  int error = s21_from_float_to_decimal(a, &b);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(from_float_to_deс_3) {  /// ????
  float a = 0.0;
  s21_decimal b = {{3123, 0, 0, 0}};
  s21_from_float_to_decimal(a, &b);
  s21_decimal m = {0};
  ck_assert_int_eq(s21_is_equal(m, b), 1);
}
END_TEST

START_TEST(from_float_to_deс_4) {  /// ????
  float a = 12345678.5;
  s21_decimal b = {{3123, 0, 0, 0}};
  s21_from_float_to_decimal(a, &b);
  s21_decimal m = {{12345680, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(m, b), 1);
}
END_TEST

START_TEST(from_float_to_deс_5) {  /// ????
  float a = 1234567.8;
  s21_decimal b = {{3123, 0, 0, 0}};
  s21_from_float_to_decimal(a, &b);
  s21_decimal m = {{1234568, 0, 0, 0}};
  // s21_set_scale(&m, 1);
  ck_assert_int_eq(s21_is_equal(m, b), 1);
}
END_TEST

Suite *create_convertor(void) {
  Suite *suite_convertor = suite_create("convert");

  TCase *from_dec_to_int = tcase_create("from_dec_to_int");
  tcase_add_test(from_dec_to_int, from_dec_to_int_1);
  // tcase_add_test(floor, other_floor_2);

  TCase *from_float_to_deс = tcase_create("from_float_to_deс");
  tcase_add_test(from_float_to_deс, from_float_to_deс_1);
  tcase_add_test(from_float_to_deс, from_float_to_deс_2);
  tcase_add_test(from_float_to_deс, from_float_to_deс_3);
  tcase_add_test(from_float_to_deс, from_float_to_deс_4);
  tcase_add_test(from_float_to_deс, from_float_to_deс_5);

  suite_add_tcase(suite_convertor, from_dec_to_int);
  suite_add_tcase(suite_convertor, from_float_to_deс);
  return suite_convertor;
}