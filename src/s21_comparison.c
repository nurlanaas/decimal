#include "s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int result = 0;
  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);
  int zero_a = s21_check_zero(a);
  int zero_b = s21_check_zero(b);
  if (zero_a == zero_b && zero_a == 1) {
    result = 0;
  } else if (zero_a == 1 && zero_b != 1 && sign_b == 0) {  // a = 0, b > 0
    result = 1;
  } else if (zero_b == 1 && zero_a != 1 && sign_a == 0) {  // b = 0, a > 0
    result = 0;
  } else if (zero_a == 1 && sign_b == 1) {  // a = 0, b < 0 result = 0
    result = 0;
  } else if (zero_b == 1 && sign_a == 1) {  // b = 0, a < 0, result = 1;
    result = 1;
  } else if (zero_a != 1 && zero_b != 1 && sign_a == 0 &&
             sign_b == 1) {  // a != 0 b != 0 a > 0 b < 0 result = 0;
    result = 0;
  } else if (zero_a != 1 && zero_b != 1 && sign_a == 1 &&
             sign_b == 0) {  // a != 0 b != 0 a < 0 b > 0 result = 1;
    result = 1;
  } else if (zero_a != 1 && zero_b != 1 && sign_a == 1 &&
             sign_b == 1) {  // a != 0 b != 0 a < 0 b <0 if (a > b) means a < b
                             // result =1 else function for comparing bits
    if (s21_compare(a, b) == 1) {  // a > b
      result = 1;
    } else {  // a = b a < b
      result = 0;
    }
  } else if (zero_a != 1 && zero_b != 1 && sign_a == 0 &&
             sign_b == 0) {  // a != 0 b != 0 a > 0 b > 0 if (a < b) means a < b
                             // result =1
    if (s21_compare(a, b) == 1 || s21_compare(a, b) == 0) {  // a>b a = b
      result = 0;
    } else {  //  a < b
      result = 1;
    }
  }
  return result;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);
  int zero_a = s21_check_zero(a);
  int zero_b = s21_check_zero(b);
  if (zero_a == zero_b && zero_a == 1) {
    result = 1;
  } else if (zero_a == zero_b && zero_a != 1 && sign_a == sign_b) {
    if (s21_compare(a, b) == 0) result = 1;
  } else {
    result = 0;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  if (s21_is_equal(a, b) == 1 || s21_is_less(a, b) == 1) {
    result = 1;
  }
  return result;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int result = 0;
  if (s21_is_less_or_equal(a, b) != 1) {
    result = 1;
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  if (s21_is_greater(a, b) == 1 || s21_is_equal(a, b) == 1) {
    result = 1;
  }
  return result;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  if (s21_is_equal(a, b) == 0) {
    result = 1;
  }
  return result;
}

int s21_compare(s21_decimal a,
                s21_decimal b) {  // a > b -> return 1, a < b -> return -1, a =
                                  // b -> return 0 не учитывая знаки
  int result = 0;
  s21_new_decimal new_a = s21_convertion(a);
  s21_new_decimal new_b = s21_convertion(b);
  if (new_b.scale > new_a.scale) {  // to equal scale_a, scale_b
    while (new_b.scale > new_a.scale) {
      s21_pointleft(&new_a);
    }
  } else if (new_b.scale < new_a.scale) {
    while (new_b.scale < new_a.scale) {
      s21_pointleft(&new_b);
    }
  }
  int end = 0;
  for (int i = 6; i >= 0 && end == 0; i--) {  // s21_compare
    if (new_a.bits[i] > new_b.bits[i]) {
      end = 1;
      result = 1;
    } else if (new_a.bits[i] < new_b.bits[i]) {
      end = 1;
      result = -1;
    }
  }
  return result;
}
