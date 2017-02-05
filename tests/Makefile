CC=gcc
pattern?=

all: driver1

clean: 
	@rm test1 test2 test3

driver1: driver1.c ../findpattern.c
	$(CC) -g -Wall -m32 $< ../findpattern.c -o test1.o
	./test1.o $(pattern)

driver2: driver2.c 
	$(CC) -m32 $< ../findpattern.c -o test2.o
	./test2.o $(pattern)

driver3: driver3.c
	$(CC) -m32 $< ../findpattern.c -o test3.o
	./test3.o $(pattern)
