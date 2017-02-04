#include "findpattern.h"

int SEGFAULT = 0; //0 = no segfault, 1 = segfault
jmp_buf env;

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
	// get access to memory (system call?)
	unsigned int mem_start = 0x00000000;
	unsigned int mem_end = 0xFFFFFFFF;

	// handler
	struct sigaction act;
	act.sa_handler = test;
	sigemptyset(&act.sa_mask);
	sigaction(SIGSEGV, &act, 0);

	// variables
	unsigned int patsfound = 0;
	unsigned int page;

	printf("getpagesize() %d\n", getpagesize());

	// cycle through pages
	for (page = mem_start; page < mem_end; page+=getpagesize()) {

		sigsetjmp(env,1);
		printf("start %d\n", page);
		//signal handler
		if (SEGFAULT == 1) {
			printf("inside - SEGFAULT %d - Page Num %d\n", SEGFAULT, page);
			SEGFAULT = 0;
			continue; // skip to next page
		}
		printf("outsidebef - SEGFAULT %d - Page Num %d\n", SEGFAULT, page);
		char x = page;
		printf("outsideaft - SEGFAULT %d - Page Num %d\n", SEGFAULT, page);

		unsigned int memory_index;
		for (memory_index=page; memory_index<=(page+getpagesize()); memory_index++) {
			unsigned int pattern_index;
			for (pattern_index=0; pattern_index<=patlength; pattern_index++) {
				if (pattern[pattern_index] == memory_index) { // the item at pattern_index is the same as the item at memory_index

					if (pattern_index == patlength) { // we are at the last item in the pattern
						printf("PAT found\n");
						if (patsfound < loclength) { // we are under the storage limit
							patternFound(memory_index, locations, patsfound); // make and store
						}
						patsfound++; // increment counter
					} else { // we are not at the last item in the pattern
						printf("%u\n", memory_index);
						continue; // check the next one
					}

				} else if (&pattern_index != &memory_index) { // we're not at a pattern
					memory_index = memory_index - pattern_index + 1; // reset memory_index
					break; // start over
				}
				memory_index++;
			}
		}
	}

	return patsfound;
}

void test (int sig) {
	printf("SEGFAULT found\n");
	printf("I am here\n");
	SEGFAULT = 1;
	siglongjmp(env, 1);
	return;
}

void patternFound(unsigned int memory_index, struct patmatch *locations, unsigned int patsfound) {
	// make patmatch
	struct patmatch temp;
	temp.location = (unsigned int) memory_index;
	temp.mode = memType(memory_index);

	locations[patsfound*3] = temp;
}

unsigned int memType(unsigned int memory_index) {
	unsigned int type = MEM_RW;

	//save sess
	jmp_buf env;
	int i;
	i = setjmp(env);

	// test write
	memory_index = '1';
	//signal handler
	if (SEGFAULT == 1) {
		type = MEM_RO;
		SEGFAULT = 0;
	}

	//return sess
	longjmp(env, 1);

	return type;
}
