#include <stdio.h>
#include <stdlib.h>

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
	// get access to memory (system call?) 
	unsigned int start = 0; 
	unsigned int end = (2^32)-1; 

	unsigned int patsfound = 0; 

	for (int memory_index=start; memory_index<=end; memory_index++) {
		for (int pattern_index=0; pattern_index<=patlength; pattern_index++) {

			if (&pattern_index == &memory_index) { // the item at pattern_index is the same as the item at memory_index

				if (pattern_index == patlength) { // we are at the last item in the pattern
					if (patsfound < loclength) { // we are under the storage limit
						patternFound(memory_index, locations); // make and store
					}
					patsfound++; // increment counter
				} else { // we are not at the last item in the pattern
					continue; // check the next one
				}

			} elseif (&pattern_index != &memory_index) { // we're not at a pattern
				memory_index = memory_index - pattern_index + 1; // reset memory_index
				break; // start over
			}
			memory_index++;
		}
	}
//lolz arjun wassup
	return patsfound;
}

void patternFound(int memory_index, struct patmatch *locations) {
	struct patmatch temp; 
	// make patmatch 
	strcpy (temp.location, memory_index); 
	strcpy (temp.mode, memType(memory_index));
	
	locations[memory_index] = temp; 
}

int isReadOnly(int memory_index) {
	if (MEM[memory_index].RW) {
		return MEM_RW; 
	} else {
		return MEM_RO; 
	}
}