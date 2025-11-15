#include "test.h"

int main(void) {
  Suite *all[] = {create_compare(),   create_add(), create_multiply(),
                  create_other(),     create_div(), create_sub(),
                  create_convertor(), NULL};
  int failed_count = 0;
  for (int i = 0; all[i] != NULL; i++) {
    SRunner *suite_runner = srunner_create(all[i]);
    srunner_run_all(suite_runner, CK_NORMAL);
    failed_count += srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// void s21_print_bits(s21_decimal a, int sign) {
//   for (int i = 2; i >= 0; i--) {
//     for (int j = 31; j >= 0 && sign == 0; j--) {
//       printf("%d", s21_get_bit(j, a.bits[i]));
//     }
//     for (int j = 31; j >= 0 && sign == 1; j--) {
//       printf("%d", s21_get_bit(j, ~a.bits[i] + 1));
//     }
//     printf(" ");
//   }
//   printf("\n");
// }

// void s21_print_64(uint64_t a) {
//   for (int j = 63; j >= 0; j--) {
//     printf("%d", s21_get_ubit(j, a));
//     if (j == 32) printf(" ");
//   }
//   printf("\n");
// }

// void s21_print_bits_64(s21_new_decimal a, int sign) {
//   for (int i = 6; i >= 0; i--) {
//     printf("%d ", i);
//     for (int j = 63; j >= 0 && sign == 0; j--) {
//       printf("%d", s21_get_ubit(j, a.bits[i]));
//       if (j == 32) printf(" ");
//     }
//     for (int j = 63; j >= 0 && sign == 1; j--) {
//       printf("%d", s21_get_ubit(j, ~a.bits[i] + 1));
//     }
//     printf("\n");
//   }
//   printf("\n");
//   //  printf("")
// }

// void s21_print_int(int a, int size) {
//   for (int j = 0; j < size; j++) {
//     printf("%d", s21_get_bit(j, a));
//   }
//   printf("\n");
// }

// void s21_print_uint(uint64_t a, int size) {
//   for (int j = 0; j < size; j++) {
//     printf("%d", s21_get_ubit(j, a));
//   }
//   printf("\n");
// }
