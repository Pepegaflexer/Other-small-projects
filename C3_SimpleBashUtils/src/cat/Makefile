CFLAGS = -Wall -Werror -Wextra

all : s21_cat

s21_cat :
	gcc $(CFLAGS) -o s21_cat s21_cat.c

clean :
	rm -f s21_cat
rebuild:
	$(MAKE) clean
	$(MAKE) all

test :
	chmod +x s21_cat
	bash mytestcat.sh

.PHONY: s21_cat