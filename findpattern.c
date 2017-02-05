#include "findpattern.h"

sigjmp_buf env; //env=0,no-segfault; env=1,segfault

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

        // cycle through pages
        for (page = mem_start; page < mem_end; page+=getpagesize()) {
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
        printf("SEGFAULT found - %d\n", sig);
        siglongjmp(env, 1);
        return;
}

void patternFound(unsigned int memory_index, struct patmatch *locations, unsigned int patsfound) {
        // make patmatch
        struct patmatch temp;
        temp.location = (unsigned int) memory_index;
        temp.mode = memType(memory_index);

        locations[patsfound] = temp;
}

unsigned int memType(unsigned int memory_index) {
        // if write segfault
        if (sigsetjmp(env,0) == 1) {
                //printf("Write SEGFAULT at %d\n", memory_index);
                return MEM_RO;
        } else {
                // test write
                memory_index = '1';
                //printf("No Write SEGFAULT at %d\n", memory_index);
                return MEM_RW;
        }
}
