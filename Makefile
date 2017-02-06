CC = gcc
CFLAG = -m32

TEST_DIR = tests

default: tests

tests:
	$(MAKE) -C $(TEST_DIR) p=$(p) 

test1: 
	$(MAKE) -C $(TEST_DIR) p=$(p) driver1 
	
test2:
	$(MAKE) -C $(TEST_DIR) p=$(p) driver2

test3: 
	$(MAKE) -C $(TEST_DIR) p=$(p) driver3

clean:
	for n in tests; do $(MAKE) -C $$n clean; done


