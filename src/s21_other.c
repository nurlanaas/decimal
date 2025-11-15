
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int scale = s21_get_scale(value);
  if (scale > 0) {
    s21_new_decimal new = s21_convertion(value);
    if (s21_get_sign(value) == 0) {  // value > 0
      for (int i = 0; i < scale; i++) {
        s21_pointright(&new);
      }
    } else if (s21_get_sign(value) == 1) {
      int flag = 0;
      for (int i = 0; i < scale; i++) {
        int remainder = s21_pointright(&new);
        if (remainder > 0) flag = 1;
      }
      if (flag == 1) {
        new.bits[0]++;
        s21_getoverflow(&new);
      }
    }
    *result = s21_convertion_to_decimal(new);
    s21_set_sign(result, s21_get_sign(value));
  } else if (scale == 0) {
    *result = value;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int scale = s21_get_scale(value);
  int remainder = 0;
  if (scale > 0) {
    s21_new_decimal new = s21_convertion(value);
    for (int i = 0; i < scale; i++) {
      remainder = s21_pointright(&new);
    }
    if (remainder >= 5) {
      new.bits[0]++;
      s21_getoverflow(&new);
    }
    *result = s21_convertion_to_decimal(new);
    s21_set_sign(result, s21_get_sign(value));
  } else if (scale == 0) {
    *result = value;
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int scale = s21_get_scale(value);
  s21_new_decimal new = s21_convertion(value);
  for (int i = 0; i < scale; i++) {
    s21_pointright(&new);
  }
  *result = s21_convertion_to_decimal(new);
  s21_set_sign(result, s21_get_sign(value));
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int sign = s21_get_sign(value);
  *result = value;
  s21_set_sign(result, sign ^ 1);
  return error;
}
