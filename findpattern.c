#include "findpattern.h"

sigjmp_buf env; //env=0,no-segfault; env=1,segfault

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
        // handler
        struct sigaction act;
        act.sa_handler = test;
        sigemptyset(&act.sa_mask);
        sigaction(SIGSEGV, &act, 0);

        // variables
        unsigned int patsfound = 0;
        unsigned int page;
	unsigned int page_num; 
	
        // cycle through pages
        for (page_num = 0; page_num < 0xFFFFFFFF/getpagesize(); page_num++) {
		page = page_num*getpagesize(); 
                unsigned int memory_index;
		 
                //signal handler
                if (sigsetjmp(env,0) == 1) {
                        printf("SEGFAULT at Page Num: %d\n", page);
                        continue; // skip to next page
                } else {
                        memory_index = page;
                        //printf("no read SEGFAULT\n");
                }

                for (memory_index=page; memory_index<=(page+getpagesize()); memory_index++) { 
                        unsigned int pattern_index;
                        for (pattern_index=0; pattern_index<=patlength; pattern_index++) {
                                if (pattern[pattern_index] == (char *)(memory_index+pattern_index)) { // the item at pattern_index is the same as the item at memory_index                                          
					printf("%c %c %c %c \n", pattern[pattern_index], pattern[pattern_index+1], pattern[pattern_index+2], pattern[pattern_index+3]); 
					printf("%c %c %c %c \n", (memory_index+pattern_index), (memory_index+pattern_index+1), (memory_index+pattern_index+2), (memory_index+pattern_index+3));
                                        if (pattern_index == patlength) { // we are at the last item in the pattern
                                                printf("PAT found\n");
                                                if (patsfound < loclength) { // we are under the storage limit
							unsigned int temp_mem = memory_index;         
							// make patmatch
						       	locations[patsfound].location = (unsigned int) memory_index;
        
						        if (sigsetjmp(env,0) == 1) {
						                //printf("Write SEGFAULT at %d\n", memory_index);
						                locations[patsfound].mode = MEM_RO;
						        } else {
						                // test write
						                memory_index = '1';
						                //printf("No Write SEGFAULT at %d\n", memory_index);
						                 locations[patsfound].mode = MEM_RW;
						        }
	
							memory_index = temp_mem; 
                                                }
                                                patsfound++; // increment counter
						memory_index += patlength - 1; //move forward so it doesn't go over these again
                                        } else { // we are not at the last item in the pattern
                                                printf("possible pattern @ %u\n", memory_index);
                                                continue; // check the next one
                                        }

                                } else if (pattern_index>0 && pattern[pattern_index] != (char *)(memory_index+pattern_index)) { // we're not at a pattern, but we thought we were
                                        break; // start over
                                }
                        }
                }
        }
	printf("patterns found: %d\n", patsfound); 
        return patsfound;
}

void test (int sig) {
        printf("SEGFAULT found - %d\n", sig);
        siglongjmp(env, 1);
        return;
}

