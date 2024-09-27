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

build: test 

test: clean
	$(CC) $(CFLAGS) tests/*.c c_source/*.c c_source/*.h $(TEST_LIBS) -o test
	./test


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
	clang-format -n c_source/*.c c_source/*.h Calculator/mainwindow.cpp
	@rm .clang-format
	
debug: clean debug_flag build
	rm -rf *.o

rebuild: clean all

valgrind: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf *.a *.o tests/*.o test *.a *.gcno *.gcda *.gcov *.info
	rm -rf ./*/*.o ./*/*.a ./*/*.gcno ./*/*.gcda ./*/*.gcov ./*/*.info
	rm -rf gcov
	rm -rf build
	rm -rf s21_smartCalc

install: clean
	mkdir build
	cd build/ && qmake ../Calculator/Calculator.pro && make

start:
	./build/Calculator

uninstall:
	rm -rf build/

dvi:
	cat readme.txt

dist: clean
	mkdir s21_smartCalc
	cp -r c_source s21_smartCalc
	cp -r Calculator s21_smartCalc
	cp Makefile s21_smartCalc
	cd s21_smartCalc
	tar cvzf s21_smartCalc/s21_smartCalc.tgz s21_smartCalc/
	
	
	

