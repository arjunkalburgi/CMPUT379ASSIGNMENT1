#ifndef _FINDPATTERN_H_
#define _FINDPATTERN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <setjmp.h>

#define MEM_RW 0
#define MEM_RO 1
#define mem_start 0
#define mem_end 4294967295

struct patmatch {
	unsigned int location;
	unsigned char mode; /* MEM_RW, or MEM_RO */
};

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength);
void signal_handler (int sig);

#endif
