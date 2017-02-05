#include "../findpattern.h"

int main(int argc, char const *argv[])
{
	// vars
	unsigned int patlength = 6; 
	unsigned int loclength = 2;
	
	//malloc memory (get a heap)
	char * heap = (char*) malloc (patlength * sizeof(char));
	
	//insert our pattern in the heap (for loop)
	int i; 
	for (i=0; i<=patlength*loclength; i++) {
		if (!(i%(patlength*2-1))) {
			int j; 
			for (j=0; j<patlength; j++) {
				heap[j] = argv[2][j];
			}
			i = i + j; 
		}
	}
	
	// run find pattern on our heap
	unsigned char pattern[patlength];
	int j; 
	for (j=0; j<patlength; j++) {
		pattern[j] = argv[2][j];
	}
	struct patmatch locations[loclength];

	findpattern (pattern, patlength, locations, loclength);
	return 0;
}
