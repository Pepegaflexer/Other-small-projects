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
	$(CC) $(CFLAGS) tests/*.c c_sources/3d_viewer.c c_sources/s21_based.c $(TEST_LIBS) -o test
	./test


gcov_flag:
	$(eval CFLAGS += --coverage -fprofile-arcs -ftest-coverage)

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
	clang-format -n c_sources/*.c c_sources/*.h 
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
	rm -rf 3dviewer

install: clean
	mkdir build
	cd build/ && qmake6 ../3D_viewerUI/3D_viewerUI.pro && make

start:
	./build/3D_viewerUI

uninstall:
	rm -rf build/

dvi:
	cat description.md

dist: clean
	mkdir 3dviewer
	cp -r c_sources 3dviewer
	cp -r 3D_viewerUI 3dviewer
	cp Makefile 3dviewer
	cd 3dviewer
	tar cvzf 3dviewer/3dviewer.tgz 3dviewer/
