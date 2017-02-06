CC=gcc
p?=
CFLAGS=-m32

all: driver1 driver2 driver3

clean: 
	@rm -f *.o

driver1: driver1.c ../findpattern.c
	$(CC) $(CFLAGS) $< ../findpattern.c -o test1.o
	./test1.o $(p)

driver2: driver2.c 
	$(CC) $(CFLAGS) $< ../findpattern.c -o test2.o
	./test2.o $(p)

driver3: driver3.c
	$(CC) $(CFLAGS) $< ../findpattern.c -o test3.o
	./test3.o $(p)
