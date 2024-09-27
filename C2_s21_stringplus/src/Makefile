CFLAGS = -Wall -Werror -Wextra -std=c11

all: clean s21_string.a test gcov_report

s21_string.a: s21_string.o s21_sprintf.o
	ar r s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a

s21_string.o: s21_string.c
	gcc -c $(CFLAGS) s21_string.c

s21_sprintf.o: s21_sprintf.c
	gcc -c $(CFLAGS) s21_sprintf.c

gcov_report: s21_string.a
	gcc --coverage $(CFLAGS) s21_string.c s21_sprintf.c s21_test.c -o s21_tests -lcheck
	./s21_tests
	lcov -t "s21_tests" -o s21_test.info -c -d .
	genhtml -o report s21_test.info

clean:
	rm -rf *.o *.a *.gcno *.gcov *.gcda *.info
	rm -rf report
	rm -rf *.dSYM

test: clean
	gcc -c -I include s21_string.c -o s21_string.o
	gcc -c -I include s21_sprintf.c -o s21_sprintf.o
	gcc -I include --coverage s21_test.c s21_string.o s21_sprintf.o -o test -lcheck -lm -g

check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm .clang-format

.PHONY: test clean all
