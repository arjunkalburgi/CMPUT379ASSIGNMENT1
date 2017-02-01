#include "findpattern.h"

int SEGFAULT = 0; //0 = no segfault, 1 = segfault

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
	// get access to memory (system call?) 
	unsigned int page_start = 0x00000000; 
	unsigned int page_end = 0xFFFFFFFF;

	// handler 
	struct sigaction act;
	act.sa_handler = test; 
	sigaction(SIGSEGV, &act, 0);

	// variables 
	unsigned int patsfound = 0; 
	unsigned int *page; 

	// cycle through pages
	for (page=(int *)page_start; page<(int *)page_end; page+=getpagesize()) {
		char x = *page; 
		//signal handler
		if (SEGFAULT == 1) {
			SEGFAULT = 0; 
			continue; // skip to next page
		}

		char * memory_index;
		for (memory_index=(char *)page; memory_index<=(char *)(page+getpagesize()); memory_index++) {
			
			printf("Tellemtellemtellemtellem\n");
			// char * pattern_index; 
			// for (pattern_index=0; pattern_index<=(char *)patlength; pattern_index++) {
			// 	if (pattern[(int)pattern_index] == *memory_index) { // the item at pattern_index is the same as the item at memory_index

			// 		if ((int)pattern_index == patlength) { // we are at the last item in the pattern
			// 			printf("PAT found\n");
			// 			if (patsfound < loclength) { // we are under the storage limit
			// 				patternFound(memory_index, locations, patsfound); // make and store
			// 			}
			// 			patsfound++; // increment counter
			// 		} else { // we are not at the last item in the pattern
			// 			printf("%s\n", *memory_index);
			// 			continue; // check the next one
			// 		}

			// 	} elseif (&pattern_index != &memory_index) { // we're not at a pattern
			// 		memory_index = memory_index - pattern_index + 1; // reset memory_index
			// 		break; // start over
			// 	}
			// 	memory_index++;
			// }
		}
	}

	
	
	return patsfound;
}

void test (int sig) {
	printf("SEGFAULT found\n"); 
	SEGFAULT = 1;
}

void patternFound(char * memory_index, struct patmatch *locations, unsigned int patsfound) {
	// make patmatch 
	struct patmatch temp; 
	strcpy (temp.location, memory_index); 
	strcpy (temp.mode, memType(memory_index));
	
	locations[patsfound*3] = temp; 
}

int memType(char * memory_index) {
	unsigned char type = MEM_RW; 
	
	//save sess
	jmp_buf env; 
	int i; 
	i = setjmp(env);

	// test write
	*memory_index = '1'; 
	//signal handler
	if (SEGFAULT == 1) {
		type = MEM_RO; 
		SEGFAULT = 0; 
	}

	//return sess
	longjmp(env, 1);

	return type; 
}
