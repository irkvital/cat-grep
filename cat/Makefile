CC=gcc
CFLAGS=-Wall -Wextra -std=c11
CFLAGS1=-fsanitize=address

all: 
	$(CC) $(CFLAGS) $(CFLAGS1)  s21_cat.c ../common/common_func.c ../common/common_func.h -lm 
clean:
	rm -rf *.a

