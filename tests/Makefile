CC=gcc
pattern?=

all: driver1

clean: 
	@rm test1 test2 test3

driver1: drivers1.c ../findpattern.c
	$(CC) -g -Wall -m32 $< ../findpattern.c -o test1.o
	./test1 $(pattern)

driver2: drivers2.c 
	$(CC) -m32 $< ../findpattern.c -o test2.o
	./test2 $(pattern)

driver3: drivers3.c
	$(CC) -m32 $< ../findpattern.c -o test3.o
	./test3 $(pattern)
