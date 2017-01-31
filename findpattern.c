#include <stdio.h>
#include <stdlib.h>

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
	// get access to memory (system call) 
	start; 
	end; 

	unsigned int patsfound = 0; 

	for (var memory=start; memory<=end; memory++) {
		for (var pattern=0; pattern<=patlength; pattern++) {
			if (&pattern == &memory) {
				if (pattern == patlength) {
					if (patsfound < loclength) {
						// make patmatch 
						// add patmatch to locations	
					}
					patsfound++; 
				}
				continue; 
			} elseif (&pattern != &memory) {
				memory = memory - pattern + 1; 
				break; 
			}
			memory++;
		}
	}

	return locations
}