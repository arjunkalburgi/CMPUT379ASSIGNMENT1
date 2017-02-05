#include "../findpattern.h"

int main(int argc, char const *argv[])
{
	// vars
	unsigned int patlength = 6; 
	unsigned int loclength = 2;
		
	//malloc memory (get a heap)
	char * heap = (char*) malloc (patlength*sizeof(char));
	//insert our pattern in the heap (for loop)
	int i; 
	for (i=0; i<patlength*loclength; i++) {
		if (!(i%(patlength*2-1))) {
			if ((i+patlength)>(patlength*loclength)) {
				memcpy(heap+i, argv[1], patlength*loclength-i); 
			} else {
				memcpy(heap+i, argv[1], patlength); 
			}
			i = i + patlength -1; 
		}
	}
	 
	// run find pattern on our heap
	unsigned char pattern[patlength];
	memcpy(pattern, argv[1], patlength); 
	struct patmatch locations[loclength];

	findpattern (pattern, patlength, locations, loclength);
	return 0;
}
