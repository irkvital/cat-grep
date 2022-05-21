CC=gcc
CFLAGS=-Wall -Wextra -std=c11
CFLAGS1=-fsanitize=address

all: s21_cat s21_grep

s21_cat:
	$(CC) $(CFLAGS) $(CFLAGS1)  ./cat/s21_cat.c ./common/common_func.c ./common/common_func.h ./cat/s21_cat.h -lm -o ./cat/s21_cat
s21_grep:
	$(CC) $(CFLAGS) $(CFLAGS1)  ./grep/s21_grep.c ./common/common_func.c ./common/common_func.h -lm -o ./grep/s21_grep
clean:
	rm -rf *.a ./cat/s21_cat ./grep/s21_grep ./common/common_func.h.gch

