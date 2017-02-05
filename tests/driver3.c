#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	// need a file desc, (open a file)
	int file = open("test.txt", O_RDWR); 

	char *c = (char *) mmap(0,10,PROT_READ,MAP_PRIVATE,file,0);
	char letter; 
	letter = *c; 
	printf("First letter: %c\n", letter);
	*c = '8';

	close(file);
}