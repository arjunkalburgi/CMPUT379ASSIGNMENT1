#include "findpattern.h"

jmp_buf env; //env=0,no-segfault; env=1,segfault

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
  // variables
  int mem_mode;
  unsigned char* page_index = 0;
  unsigned int mem_index = 0;
  unsigned int pat_index = 0;
  unsigned char test;
  unsigned int patsfound = 0;

  // handler
  struct sigaction act;
  act.sa_handler = signal_handler;
  sigemptyset(&act.sa_mask);
  sigaction(SIGSEGV, &act, 0);

  // cycle through pages
  for (page_index = 0; page_index < (unsigned char *) mem_end; page_index += getpagesize()) {

    //signal handler
    if (sigsetjmp(env,1) == 0) {
      signal(SIGSEGV, signal_handler);
      test = *page_index;
      if (sigsetjmp(env,1) == 0) {
        signal(SIGSEGV, signal_handler);
        *page_index = test;
        mem_mode = MEM_RW;
      }
      mem_mode = MEM_RO;
    } else {
      continue;
    }

    for (mem_index = 0; mem_index < (unsigned int) page_index + getpagesize(); mem_index++) {
      if (sigsetjmp(env,1) == 0) {
        signal(SIGSEGV, signal_handler);
        for (pat_index = 0; pat_index <= patlength; pat_index++) {
          if (pattern[pat_index] != page_index[mem_index + pat_index]) {
            if (pat_index == patlength) {
              if (patsfound < loclength) {
                locations[patsfound].location = (unsigned int) page_index + (unsigned int) mem_index;
                locations[patsfound].mode = mem_mode;
              }
              patsfound++;
            }
          }
        }
      }
      break;
    }

  }

  return patsfound;
}

void signal_handler (int sig) {
  siglongjmp(env, 1);
  return;
}
