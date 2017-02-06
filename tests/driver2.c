#include "../findpattern.h"

// create local instances of the pattern on the stack. To do this you need to think of how you can store an instance of 
// the pattern on the stack only after your first call to findpattern().

int main(int argc, char const *argv[])
{
	struct patmatch locations;
	unsigned int loclength;

	char pattern[6] = "CANADA";

	char pattern1[6] = "CANADA";
	char var1[6] = "BANANA";
	char var2[8] = "LALALAND";
	char pattern2[6] = "CANADA";
	
	// run find pattern on our stack
	findpattern (&pattern, 6, locations, loclength)
	return 0;
}