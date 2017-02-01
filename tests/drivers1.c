#include "../findpattern.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	//malloc memory (get a heap)
	char * heap = (char*) malloc (12);
	//insert our pattern in the heap (for loop)
	heap[0] = 'c';
	heap[1] = 'a';
	heap[2] = 'n';
	heap[3] = 'a';
	heap[4] = 'd';
	heap[5] = 'a';
	heap[6] = 'c';
	heap[7] = 'a';
	heap[8] = 'n';
	heap[9] = 'a';
	heap[10] = 'd';
	heap[11] = 'a';
	
	// run find pattern on our heap
	unsigned int patlength = 6; 
	unsigned char pattern[patlength];
	pattern[0] = 'c'; 
	pattern[1] = 'a'; 
	pattern[2] = 'n'; 
	pattern[3] = 'a'; 
	pattern[4] = 'd'; 
	pattern[5] = 'a'; 
	unsigned int loclength = 2;
	struct patmatch locations[loclength];

	findpattern (pattern, patlength, locations, loclength);
	return 0;
}