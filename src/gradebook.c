#include <stdio.h>
#include <stdlib.h>
#include "gradebook.h"


#define MAX_LINE 1000

int main(int argc, char ** argv) {
	FILE *bob = fopen(argv[1], "r");
	if(bob == NULL) fprintf(stderr, "Could not open %s!\n", argv[1]);
	char * john = malloc(MAX_LINE * sizeof(char));
	while(fgets(john, MAX_LINE, bob))
		printf("%s", john);
	return 0;
}

