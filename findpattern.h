#define MEM_RW 0
#define MEM_RO 1

struct patmatch {
	unsigned int location;
	unsigned char mode; /* MEM_RW, or MEM_RO */
};

unsigned int findpattern (unsigned char *pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength);
void patternFound(int memory_index, struct patmatch *locations); 
int memType(int memory_index); 
