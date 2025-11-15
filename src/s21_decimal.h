#ifndef DECIMAL
#define DECIMAL

#include <math.h>    // pow
#include <stdint.h>  // чтобы точно контролировать размер байтов на тип

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  uint64_t bits[7];  // 64 для борьбы с переполнением
  uint16_t scale;
} s21_new_decimal;

#define MINUS 0x80000000             // 10... 0.. 0.. 0..
#define SCALE 0x00ff0000             // 0.. 11111111 0.. 0..
#define MAX4BITE 0x00000000ffffffff  // 4 байта равные единице
#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MAXINT 2147483647
#define MININT -2147483648
#define POSITIVE_INFINITY 1.0f / 0.0f
#define NEGATIVE_INFINITY -1.0f / 0.0f
#define S21_NAN 0.0 / 0.0

// s21_common
int s21_get_scale(s21_decimal value);
int s21_get_bit(int k, int n);
int s21_get_ubit(int k, uint64_t n);
int s21_get_sign(s21_decimal value);
int s21_check_zero(s21_decimal a);

void s21_set_ubit(s21_new_decimal *value, int bit, int v);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_sign(s21_decimal *value, int sign);

s21_new_decimal s21_convertion(s21_decimal value);
s21_decimal s21_convertion_to_decimal(s21_new_decimal value);

void s21_pointleft(s21_new_decimal *a);
uint64_t s21_pointright(s21_new_decimal *a);
int s21_getoverflow(s21_new_decimal *a);
int s21_normalization(s21_new_decimal *a);
void s21_bankround(s21_new_decimal *a, uint64_t remainder, int flag);

// s21_comparison
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_compare(s21_decimal a, s21_decimal b);

// s21_arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_multiply(s21_decimal value_1, s21_decimal value_2,
                 s21_new_decimal *mult, int different_sign);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_division(s21_decimal value_1, s21_decimal value_2,
                  s21_new_decimal *res);

s21_new_decimal s21_sum(s21_decimal value_1, s21_decimal value_2,
                        int different_sign);
void s21_check_max(s21_decimal *result, int *error);
void s21_shift(s21_new_decimal *res, int n);
void s21_raznost(s21_new_decimal *mod, s21_new_decimal new_b);
void s21_plus_fraction_division(s21_new_decimal *a,
                                s21_new_decimal fraction_devision);
void s21_div_integer(s21_new_decimal new_a, s21_new_decimal new_b,
                     s21_new_decimal *mod, s21_new_decimal *res);
int s21_compare_new(s21_new_decimal new_a, s21_new_decimal new_b);

// s21_convertors
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
void s21_more_then_7(float src, s21_decimal *dst);
void s21_less_then_7(float src, s21_decimal *dst);
long double s21_to_ldouble(s21_decimal a);

// s21_other
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif