#ifndef TEST
#define TEST

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite *create_compare(void);
Suite *create_add(void);
Suite *create_sub(void);
Suite *create_multiply(void);
Suite *create_div(void);
Suite *create_other(void);
Suite *create_convertor(void);

// void s21_print_bits(s21_decimal a, int sign);
// void s21_print_int(int a, int size);
// void s21_print_uint(uint64_t a, int size);
// void s21_print_bits_64(s21_new_decimal a, int sign);
// void s21_print_64(uint64_t a);

#endif
