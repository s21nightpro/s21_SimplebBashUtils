CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror
GREP= s21_grep.c s21_grep.h

all: 
	$(CC) $(CFLAGS) $(GREP) -o s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(GREP) -o s21_grep

test:
	chmod 777 test.sh
	./test.sh

clean:
	rm -rf s21_grep
	rm -rf *.a *.out *.o *.txt

rebuild:
	make clean
	make all
	rm -rf  *.o *.a s21_grep