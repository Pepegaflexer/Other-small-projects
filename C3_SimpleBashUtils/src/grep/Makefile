CFLAGS = -Wall -Werror -Wextra

all : s21_grep

s21_grep :
	gcc $(CFLAGS) -o s21_grep s21_grep.c

clean :
	rm -f s21_grep

rebuild:
	$(MAKE) clean
	$(MAKE) all


test :
	chmod +x s21_cat
	bash mytestgrep.sh

.PHONY: s21_grep