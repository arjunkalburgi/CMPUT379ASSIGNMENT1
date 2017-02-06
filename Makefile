CC = gcc
CFLAG = -m32
p?=

default: 
	for n in tests; do $(MAKE) -C pattern=p $$n; done > tests/test_results.txt 

clean:
	for n in tests; do $(MAKE) -C $$n clean; done


