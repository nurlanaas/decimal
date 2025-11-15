CC=gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 
CFILES = $(wildcard *.c)
OFILES = $(patsubst %.c,%.o, ${CFILES})
TESTS_CFILES = $(wildcard tests/*.c)
OS_NAME = $(shell uname -s)

ifeq ($(OS_NAME),Linux) 
	LIB_FLAGS = $(shell pkg-config --libs check)
endif
ifeq ($(OS_NAME),Darwin)
	LIB_FLAGS = $(shell pkg-config --libs check)
endif

all: s21_decimal.a test gcov_report

s21_decimal.a: ${CFILES}
	${CC} -c $(CFLAGS) $(LIB_FLAGS) $(CFILES)
	ar rcs $@ $(OFILES)
	ranlib s21_decimal.a
	-rm -rf *.o
	
# test1: 
# 	$(CC) $(CFILES) sss/test1.c

test: s21_decimal.a
	${CC} $(CFLAGS) -o test $(TESTS_CFILES) s21_decimal.a $(LIB_FLAGS)
	./test

gcov_report:${CFILES}
	gcc --coverage ${CFILES} ${TESTS_CFILES} -o test $(LIB_FLAGS) 
	./test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info

clean:
	-rm -rf *.o *.gcda *.gcno *.gcov *result coverage.info s21_test.info s21_decimal.a test report a.out

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i -style=Google ${CFILES} ${TESTS_CFILES} *.h tests/*.h
	clang-format -n -style=Google ${CFILES} ${TESTS_CFILES} *.h tests/*.h
	rm .clang-format

rebuild: clean all

