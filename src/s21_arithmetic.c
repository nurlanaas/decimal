#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign_a = s21_get_sign(value_1);
  int sign_b = s21_get_sign(value_2);
  int zero_a = s21_check_zero(value_1);
  int zero_b = s21_check_zero(value_2);
  s21_new_decimal s21_summa = {0};
  if (zero_a == 1) {
    *result = value_2;
    if (zero_b == 1) {
      s21_set_sign(result, 0);
    }
  } else if (zero_b == 1) {
    *result = value_1;
    if (zero_a == 1) s21_set_sign(result, 0);
  } else if (sign_a == sign_b) {
    s21_summa = s21_sum(value_1, value_2, 0);
    int overflow = s21_normalization(&s21_summa);  //
    if (overflow > 0) {
      if (sign_a == 1) error = 2;
      if (sign_a == 0) error = 1;
    } else {
      *result = s21_convertion_to_decimal(s21_summa);
      s21_set_sign(result, sign_a);
    }
  } else if (sign_a != sign_b) {
    int sign_diff = 0;
    if (s21_compare(value_1, value_2) == 1) {
      s21_summa = s21_sum(value_1, value_2, 1);  // модуль разности
      if (sign_a == 1) sign_diff = 1;            //
      if (sign_a == 0) sign_diff = 0;
    } else if (s21_compare(value_1, value_2) == -1) {
      s21_summa = s21_sum(value_2, value_1, 1);
      if (sign_b == 1) sign_diff = 1;
      if (sign_b == 0) sign_diff = 0;
    } else if (s21_compare(value_1, value_2) == 0) {
      s21_summa = s21_sum(value_2, value_1, 1);
    }
    s21_normalization(&s21_summa);  //
    *result = s21_convertion_to_decimal(s21_summa);
    s21_set_sign(result, sign_diff);
  }
  s21_check_max(result, &error);
  return error;
}

void s21_check_max(s21_decimal *result, int *error) {
  s21_decimal check = {{0b11111111111111111111111111111111,
                        0b11111111111111111111111111111111,
                        0b11111111111111111111111111111111, 0}};
  int check_range = 0;
  for (int i = 0; i < 3 && s21_get_scale(*result) == 0; i++) {
    if (check.bits[i] == result->bits[i]) check_range++;
  }
  if (check_range == 3) {
    *error = 1;
    if (s21_get_sign(*result) == 1) *error = 2;
  }
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_get_sign(value_2) == 1) {
    s21_set_sign(&value_2, 0);
  } else {
    s21_set_sign(&value_2, 1);
  }
  int error = s21_add(value_1, value_2, result);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign_a = s21_get_sign(value_1);
  int sign_b = s21_get_sign(value_2);
  int zero_a = s21_check_zero(value_1);
  int zero_b = s21_check_zero(value_2);
  s21_new_decimal mult = {0};
  if (zero_a == 1 || zero_b == 1) {
    s21_decimal m = {0};
    *result = m;
  } else if (sign_a == sign_b) {
    error = s21_multiply(value_1, value_2, &mult, 0);
    if (error == 0) {
      *result = s21_convertion_to_decimal(mult);
      s21_set_sign(result, 0);
    }
  } else if (sign_a != sign_b) {
    error = s21_multiply(value_1, value_2, &mult, 1);
    if (error == 0) {
      *result = s21_convertion_to_decimal(mult);
      s21_set_sign(result, 1);
    }
  }
  s21_decimal check = {{0b11111111111111111111111111111111,
                        0b11111111111111111111111111111111,
                        0b11111111111111111111111111111111, 0}};
  int check_range = 0;
  for (int i = 0; i < 3 && s21_get_scale(*result) == 0; i++) {
    if (check.bits[i] == result->bits[i]) check_range++;
  }
  if (check_range == 3) {
    error = 1;
    if (s21_get_sign(*result) == 1) error = 2;
  }
  return error;
}

int s21_multiply(s21_decimal value_1, s21_decimal value_2,
                 s21_new_decimal *mult, int different_sign) {
  s21_new_decimal new_a = s21_convertion(value_1);
  s21_new_decimal new_b = s21_convertion(value_2);
  int error = 0;
  mult->bits[0] = new_a.bits[0] * new_b.bits[0];
  mult->bits[1] = new_a.bits[1] * new_b.bits[0] + new_a.bits[0] * new_b.bits[1];
  mult->bits[2] = new_a.bits[2] * new_b.bits[0] +
                  new_a.bits[1] * new_b.bits[1] + new_a.bits[0] * new_b.bits[2];
  mult->bits[3] = new_a.bits[2] * new_b.bits[1] + new_a.bits[1] * new_b.bits[2];
  mult->bits[4] = new_a.bits[2] * new_b.bits[2];
  mult->scale = new_a.scale + new_b.scale;
  s21_getoverflow(mult);
  int overflow = s21_normalization(mult);
  if (overflow > 0 && different_sign == 0) error = 1;
  if (overflow > 0 && different_sign == 1) error = 2;
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign_a = s21_get_sign(value_1);
  int sign_b = s21_get_sign(value_2);
  int zero_a = s21_check_zero(value_1);
  int zero_b = s21_check_zero(value_2);
  s21_new_decimal res = {0};
  if (zero_b == 1) {
    error = 3;
  } else if (zero_a == 1) {
    s21_decimal m = {0};
    *result = m;
  } else {
    s21_division(value_1, value_2, &res);
    int overflow = s21_normalization(&res);
    if (overflow > 0 && (sign_a == sign_b)) error = 1;
    if (overflow > 0 && (sign_a != sign_b)) error = 2;
  }
  if (error == 0) {
    *result = s21_convertion_to_decimal(res);
    s21_set_sign(result, sign_a ^ sign_b);
  }
  s21_decimal check = {{0b11111111111111111111111111111111,
                        0b11111111111111111111111111111111,
                        0b11111111111111111111111111111111, 0}};
  int check_range = 0;
  for (int i = 0; i < 3 && s21_get_scale(*result) == 0; i++) {
    if (check.bits[i] == result->bits[i]) check_range++;
  }
  if (check_range == 3) {
    error = 1;
    if (s21_get_sign(*result) == 1) error = 2;
  }
  return error;
}

void s21_division(s21_decimal value_1, s21_decimal value_2,
                  s21_new_decimal *res) {  // value1 value2 sign = 0
  s21_new_decimal new_a = s21_convertion(value_1);
  s21_new_decimal new_b = s21_convertion(value_2);
  if (new_b.scale > new_a.scale) {  // to equal scale_a, scale_b
    while (new_b.scale > new_a.scale) {
      s21_pointleft(&new_a);
    }
  } else if (new_b.scale < new_a.scale) {
    while (new_b.scale < new_a.scale) {
      s21_pointleft(&new_b);
    }
  }
  s21_new_decimal mod = {0};
  s21_div_integer(new_a, new_b, &mod, res);
  while (mod.bits[0] != 0 &&
         res->scale <= 30) {  //  меньше 30 для банк округления
    s21_pointleft(&mod);
    s21_pointleft(res);
    s21_new_decimal fraction_s21_division = {0};
    s21_new_decimal fraction_remainder = {0};
    if (s21_compare_new(mod, new_b) == 1 ||
        s21_compare_new(mod, new_b) == 0) {  // mod >= new_b
      s21_div_integer(
          mod, new_b, &fraction_remainder,
          &fraction_s21_division);  // fraction_s21_division = mod / new_b ;
                                    // fraction_remainder =  mod % new_b
      s21_plus_fraction_division(res,
                                 fraction_s21_division);  // res += mod / new_b

      for (int i = 0; i < 7; i++) {
        mod.bits[i] = fraction_remainder.bits[i];
      }
    }
  }
}

void s21_plus_fraction_division(s21_new_decimal *a,
                                s21_new_decimal fraction_devision) {
  for (int i = 0; i < 7; i++) {
    a->bits[i] = a->bits[i] + fraction_devision.bits[i];
  }
  s21_getoverflow(a);
}

void s21_div_integer(
    s21_new_decimal new_a, s21_new_decimal new_b, s21_new_decimal *mod,
    s21_new_decimal *res) {  // записывать в res результат new_a/new_b целой
                             // части деления, остаток записывать в mod
  int integer = 0;
  int fraction = 0;
  int significant = -1;
  for (int i = 223; i >= 0 && significant == -1;
       i--) {  // узнали старший бит где лежит в делимом
    integer = i / 32;
    fraction = i % 32;
    if (s21_get_ubit(fraction, new_a.bits[integer]) == 1) {
      significant = i;
    }
  }
  int current = -1;
  for (int i = significant; i >= 0; i--) {
    current =
        s21_get_ubit(i % 32, new_a.bits[i / 32]);  // текущий бит в делимом
    s21_set_ubit(mod, 0, current);
    if (s21_compare_new(*mod, new_b) == 1 ||
        s21_compare_new(*mod, new_b) == 0) {  // mod >= new_b
      s21_raznost(mod, new_b);
      s21_set_ubit(res, 0, 1);
    } else if (s21_compare_new(*mod, new_b) == -1) {  // mod < new_b
      s21_set_ubit(res, 0, 0);
    }
    if (i > 0) {
      s21_shift(mod, 1);
      s21_shift(res, 1);
    }
  }
}

int s21_compare_new(
    s21_new_decimal new_a,
    s21_new_decimal new_b) {  // a > b -> return 1, a < b -> return -1, a = b ->
                              // return 0 не учитывая знаки
  int result = 0;
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

void s21_raznost(s21_new_decimal *mod, s21_new_decimal new_b) {  // mod -= new_b
  for (int i = 0; i < 7; i++) {
    new_b.bits[i] = ~new_b.bits[i] + 1;
    mod->bits[i] += new_b.bits[i];  // лежит остаток
  }
  s21_getoverflow(mod);
}

void s21_shift(s21_new_decimal *res, int n) {
  int fraction = n % 32;
  for (int j = 6; j >= 0; j--) {
    res->bits[j] = res->bits[j] << fraction;
  }
  s21_getoverflow(res);
}

s21_new_decimal s21_sum(s21_decimal value_1, s21_decimal value_2,
                        int different_sign) {  // // value_1 > value_2 по модулю
  s21_new_decimal new_a = s21_convertion(value_1);
  s21_new_decimal new_b = s21_convertion(value_2);
  s21_new_decimal result = {0};
  for (int i = 0; i < 3 && different_sign == 1; i++) {
    new_b.bits[i] = ~new_b.bits[i] + 1;
  }
  if (new_b.scale > new_a.scale) {  // to equal scale_a, scale_b
    while (new_b.scale > new_a.scale) {
      s21_pointleft(&new_a);
    }
  } else if (new_b.scale < new_a.scale) {
    while (new_b.scale < new_a.scale) {
      s21_pointleft(&new_b);
    }
  }
  for (int i = 0; i < 7; i++) {
    result.bits[i] = new_a.bits[i] + new_b.bits[i];
  }
  result.scale = new_a.scale;
  s21_getoverflow(&result);
  return result;
}