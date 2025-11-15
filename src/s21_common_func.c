
#include "s21_decimal.h"

int s21_get_bit(int k,
                int n) {  // получает значение k бита в числе n. нужно исп
  return (n >> k) & 1;
}

int s21_get_ubit(int k,
                 uint64_t n) {  // получает значение k бита в числе n. нужно исп
  return (n >> k) & 1;
}

void s21_set_ubit(s21_new_decimal *value, int bit, int v) {
  int bite = bit / 32;
  int b = bit % 32;
  value->bits[bite] |= (v << b);
}

int s21_get_scale(
    s21_decimal value) {  // возвращаем степень числа отвечающего за запятую
  return (value.bits[3] & SCALE) >> 16;
}

void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= MINUS;
  value->bits[3] |= (scale << 16) & SCALE;
}

void s21_set_sign(s21_decimal *value, int sign) {
  if (sign == 1) value->bits[3] |= MINUS;  // поставили 1 в знак
  if (sign == 0) value->bits[3] &= ~MINUS;
}

int s21_get_sign(s21_decimal value) {
  return ((value.bits[3] & MINUS) != 0);  // 1 = -
}

int s21_check_zero(s21_decimal a) {
  int is_zero = 0;
  for (int i = 0; i < 3; i++) {
    if (a.bits[i] == 0) {
      is_zero++;
    }
  }
  if (is_zero == 3) {
    is_zero = 1;
  } else {
    is_zero = 0;
  }
  return is_zero;
}

int s21_getoverflow(s21_new_decimal *a) {
  int overflow = 0;
  for (int i = 0; i < 7; i++) {
    a->bits[i] += overflow;
    overflow = a->bits[i] >> 32;
    a->bits[i] &= MAX4BITE;
  }
  return overflow;
}

void s21_pointleft(s21_new_decimal *a) {
  for (int i = 0; i < 7; i++) {
    a->bits[i] *= 10;
  }
  s21_getoverflow(a);
  a->scale++;
}

uint64_t s21_pointright(s21_new_decimal *a) {
  uint64_t remainder = 0;
  for (int i = 6; i >= 0; i--) {
    a->bits[i] += remainder << 32;
    remainder = a->bits[i] % 10;
    a->bits[i] /= 10;  // сдвинется снова в правые 32 бита
  }
  a->scale--;
  return remainder;  // если >5, округляем
}

int s21_normalization(s21_new_decimal *a) {
  int flag = 0;
  uint64_t remainder = 0;
  for (int i = 6; i > 2; i--) {
    while (a->scale > 0 && a->bits[i] != 0) {
      remainder = s21_pointright(a);
      if (remainder != 0) flag++;
    }
  }
  while (a->scale > 28) {
    remainder = s21_pointright(a);
    if (remainder != 0) flag++;
  }
  s21_bankround(a, remainder, flag);
  int res = 0;
  for (int i = 6; i > 2; i--) {  // check overflow
    if (a->bits[i] != 0) res = 1;
  }
  return res;
}

void s21_bankround(s21_new_decimal *a, uint64_t remainder, int flag) {
  if (remainder > 5 || (remainder == 5 && flag > 1)) {
    a->bits[0]++;
    s21_getoverflow(a);
  } else if (remainder == 5 && flag == 1) {
    if ((a->bits[0] % 10) % 2 != 0) {
      a->bits[0]++;
      s21_getoverflow(a);
    }
  }
}

s21_new_decimal s21_convertion(s21_decimal value) {
  s21_new_decimal a = {0};
  for (int i = 0; i < 3; i++) {
    a.bits[i] = (uint64_t)(value.bits[i] & MAX4BITE);
  }
  a.scale = (uint16_t)s21_get_scale(value);
  return a;
}

s21_decimal s21_convertion_to_decimal(s21_new_decimal value) {
  s21_decimal a = {0};
  for (int i = 0; i < 3; i++) {
    a.bits[i] = value.bits[i] & MAX4BITE;
  }
  s21_set_scale(&a, value.scale);
  return a;
}