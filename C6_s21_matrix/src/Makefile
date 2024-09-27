CC = gcc
C_LIBS := -lm
TEST_LIBS := -lcheck $(shell pkg-config --libs check)
ifeq ($(shell uname), Linux)
TEST_LIBS := $(shell pkg-config --libs check) -lpthread -lrt -lm
endif
CFLAGS = -std=c11 -Wall -Werror -Wextra
SOURCES = $(wildcard s21_*.c) 

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))



all: build

build: test s21_matrix.a

test: s21_matrix.a
	$(CC) $(CFLAGS) tests/*.c s21_matrix.a $(TEST_LIBS) -o test
	./test

s21_matrix.a: $(OBJECTS)
	ar rcs s21_matrix.a $(OBJECTS)
	ranlib s21_matrix.a

gcov_flag:
	$(eval CFLAGS += --coverage)

debug_flag:
	$(eval CFLAGS += -g)

gcov_report: clean gcov_flag test
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf *.gcno *.gcda *.gcov
	open ./gcov/index.html

check:
	@cp ../materials/linters/.clang-format .
	clang-format -n *.h *.c ././*.c ././*.h ./*.c ./*.h
	@rm .clang-format

style:
	@cp ../materials/linters/.clang-format .
	clang-format -i *.h ./*/*.c ./*/*.h *.c
	@rm .clang-format
	
debug: clean debug_flag build
	rm -rf *.o

rebuild: clean all

valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf *.a *.o tests/*.o test *.a *.gcno *.gcda *.gcov *.info
	rm -rf ./*/*.o ./*/*.a ./*/*.gcno ./*/*.gcda ./*/*.gcov ./*/*.info
	rm -rf gcov
