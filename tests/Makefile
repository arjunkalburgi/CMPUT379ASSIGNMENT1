CC=gcc
pattern?=

all: drivers1

clean: 
	@rm test1 test2 test3

driver1: drivers1.c findpattern
	$(CC) -m32 $< -o test1
	./test1 $(pattern)

driver2: drivers2.c findpattern
	$(CC) -m32 $< -o test2
	./test2 $(pattern)

driver3: drivers3.c findpattern
	$(CC) -m32 $< -o test3
	./test3 $(pattern)

findpattern: ../findpattern.c
	@$(CC) -m32 $< 