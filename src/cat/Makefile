CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror
CAT= s21_cat.c

all: 
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

test:
	chmod 777 test_func_cat.sh
	./test_func_cat.sh

clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o *.txt

rebuild:
	make clean
	make all
	rm -rf  *.o *.a