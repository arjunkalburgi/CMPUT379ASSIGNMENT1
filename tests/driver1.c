#include "../findpattern.h"

int main(int argc, char const *argv[])
{
	// vars
	unsigned int patlength = 6; 
	unsigned int loclength = 2;
		
	//malloc memory (get a heap)
	char * heap = (char*) malloc (patlength*loclength);
	//insert our pattern in the heap (for loop)
	int i; 
	for (i=0; i<patlength*loclength; i++) {
		if (!(i%(patlength*2-1))) {
			int j = 0;
			heap[0] = argv[1][0];
			for (j=0; j<patlength; j++) {
				if (patlength >= i+j) {
					heap[j] = argv[1][j];
				}
			}
			i = i + j; 
		}
	}
	 
	// run find pattern on our heap
	unsigned char pattern[patlength];
	int j; 
	for (j=0; j<patlength; j++) {
		pattern[j] = argv[1][j];
	}
	struct patmatch locations[loclength];

	findpattern (pattern, patlength, locations, loclength);
	return 0;
}
