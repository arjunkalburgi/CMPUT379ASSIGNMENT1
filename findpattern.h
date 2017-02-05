#ifndef _FINDPATTERN_H_
#define _FINDPATTERN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>

#define MEM_RW 0
#define MEM_RO 1

#define mem_start 0x00000000; 
#define mem_end 0xFFFFFFFF; 

struct patmatch {
	unsigned int location;
	unsigned char mode; /* MEM_RW, or MEM_RO */
};

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength);
void test (int sig);
void patternFound(unsigned int memory_index, struct patmatch *locations, unsigned int patsfound);
unsigned int memType(unsigned int memory_index);

#endif
