#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  int count = 0;
  *dst = 0;
  long double a = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      a += s21_get_bit(j, src.bits[i]) * pow(2, count);
      count++;
    }
  }
  a /= pow(10, s21_get_scale(src));
  if (s21_get_sign(src) == 1) a = -a;
  *dst = a;
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  *dst = 0;
  long double ans = s21_to_ldouble(src);
  if (ans > MAXINT || ans < MININT) {
    error = 1;
  } else {
    *dst = (int)ans;
  }
  return error;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  if (src < 0) {
    src = -src;
    s21_set_sign(dst, 1);
  }
  dst->bits[0] = src;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_decimal m = {0};
  *dst = m;
  int error = 0, sign = 0;
  if (src < 0) {
    src = -src;
    sign = 1;
  }
  if ((src > 0 && src < 1e-28) || src == POSITIVE_INFINITY ||
      src == NEGATIVE_INFINITY || src == S21_NAN) {
    error = 1;
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
  } else if (src > MAX_DECIMAL) {
    error = 1;
  } else if (src == 0) {
    dst->bits[0] = 0;
  } else {
    int scale = 0;
    int significant_count = 0;
    int round_digit = 0;
    if (src < 1) {
      while (src < 1) {
        src *= 10;
        scale++;
      }
      significant_count++;
      while (significant_count < 7) {
        src *= 10;
        significant_count++;
        scale++;
      }
      s21_set_scale(dst, scale);
      round_digit = (int)(src * 10) % 10;
      if (round_digit > 5) src++;
      dst->bits[0] = (int)src;
    } else if (src >= pow(10, 7)) {  // >7 знач цифр до запятой
      s21_more_then_7(src, dst);
    } else if (src >= pow(10, 6) &&
               src < pow(10, 7)) {  // 7 знач цифр до запятой
      round_digit = (int)(src * 10) % 10;
      if (round_digit >= 5) src++;
      dst->bits[0] = (int)src;
    } else if (src < pow(10, 6)) {
      s21_less_then_7(src, dst);
    }
    s21_set_sign(dst, sign);
  }
  return error;
}

void s21_more_then_7(float src, s21_decimal *dst) {
  int round_digit = 0;
  int count = 0;  // столько раз нужно умножить decimal на 10
  while (src >= pow(10, 7)) {
    round_digit = (uint64_t)src % 10;
    src /= 10;
    count++;
  }
  if (round_digit >= 5) src++;
  s21_new_decimal new = {0};
  new.bits[0] = (uint64_t)src;
  for (int i = 0; i < count; i++) {
    s21_pointleft(&new);
  }
  s21_normalization(&new);
  new.scale = 0;
  *dst = s21_convertion_to_decimal(new);
}

void s21_less_then_7(float src, s21_decimal *dst) {
  int round_digit = 0;
  int num = 0;  // кол-во знач цифр до запятой
  while (src >= pow(10, num)) {
    num++;
  }
  int scale = 7 - num;
  src *= pow(10, scale);
  round_digit = (int)(src * 10) % 10;
  if (round_digit >= 5) src++;
  dst->bits[0] = (int)src;
  s21_set_scale(dst, scale);
}

long double s21_to_ldouble(s21_decimal a) {
  long double res = 0;
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      res += s21_get_bit(j, a.bits[i]) * pow(2, count);
      count++;
    }
  }
  res /= pow(10, s21_get_scale(a));
  if (s21_get_sign(a) == 1) res = -res;
  return res;
}