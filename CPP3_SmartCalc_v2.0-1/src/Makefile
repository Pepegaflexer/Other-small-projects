CXX = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra
TEST_LIBS := -lgtest -lgtest_main -lpthread

SOURCES = Calculator/Tests/*.cc Calculator/Model/*.cc

all : install open

test: clean
	@$(CXX) $(CPPFLAGS) $(SOURCES) -o test $(TEST_LIBS)
	@./test


install:
	make clean
	rm -rf build
	mkdir build
	cd Calculator && qmake && make && make clean && rm Makefile && cd ../ && mv Calculator/Calculator build

open:
	build/Calculator

uninstall:
	rm -rf build*

dvi:
	open readme.md

dist:
	make clean
	tar --totals -cvf Calculator.tar Calculator Makefile readme.md

clean:
	rm -rf *.a *.o tests/*.o test *.a *.info *.tar
	rm -rf ./*/*.o ./*/*.a ./*/*.info
	rm -rf gcov
	rm -rf leaks
	rm -rf *.dSYM
	rm -rf ./*/*.pro.user
	rm -f ./*/.qmake.stash
	rm -rf build-*


check_style:
	clang-format -style=google -n Calculator/Controller/*.*
	clang-format -style=google -n Calculator/Model/*.*
	clang-format -style=google -n Calculator/View/*.*
	clang-format -style=google -n Calculator/Tests/*.*
	clang-format -style=google -n Calculator/main.cc

format_style:
	clang-format -style=google -i Calculator/Controller/*.*
	clang-format -style=google -i Calculator/Model/*.*
	clang-format -style=google -i Calculator/View/*.*
	clang-format -style=google -i Calculator/Tests/*.*
	clang-format -style=google -i Calculator/main.cc
	
rebuild: clean all


leak: clean test
	valgrind --tool=memcheck --leak-check=yes  ./test
