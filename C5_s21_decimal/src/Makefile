CC = gcc
C_LIBS := -lm
TEST_LIBS := -lcheck $(shell pkg-config --libs check)
ifeq ($(shell uname), Linux)
TEST_LIBS := $(shell pkg-config --libs check) -lpthread -lrt -lm
endif
CFLAGS = -std=c11 -Wall -Werror -Wextra
SOURCES = $(wildcard s21_*.c) \
	$(wildcard ./big_decimal/s21_*.c) \
	$(wildcard ./arithmetic/s21_*.c) \
	$(wildcard ./converters/s21_*.c) \
	$(wildcard ./comparision/s21_*.c) \
	$(wildcard ./bitwise_arithmetic/s21_*.c) \
	$(wildcard ./helpers/s21_*.c) \
	$(wildcard ./other/s21_*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

# SOURCES += $(wildcard ./big_decimal/debug*.c) # dubug .c files

all: build

build: test s21_decimal.a

test: s21_decimal.a
	$(CC) $(CFLAGS) tests/*.c s21_decimal.a $(TEST_LIBS) -o test
	./test

s21_decimal.a: $(OBJECTS)
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

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
	clang-format -n *.h ./*/*.c ./*/*.h
	@rm .clang-format

style:
	@cp ../materials/linters/.clang-format .
	clang-format -i *.h ./*/*.c ./*/*.h
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
