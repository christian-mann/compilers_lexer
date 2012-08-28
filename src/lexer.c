#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int main(int argc, char **argv) {
	//open the file given as an argument
	char *sfSrc;
	FILE *fSrc;
	if(argc > 1) {
		sfSrc = argv[1];
		if(!(fSrc = fopen(sfSrc, "r"))) {
			fprintf(stderr, "Error: No source file found at %s\n", sfSrc);
			return -1;
		}
	} else {
		fprintf(stderr, "Warning: No source file given; using stdin\n");
		fSrc = stdin;
	}

	//begin reading a line at a time
	char sLine[74]; //72 characters per line + '\n' + '\0'
	int cLine = 1;
	while(fgets(sLine, sizeof(sLine), fSrc) != NULL) {
		//strip trailing '\n' if it exists
		int len = strlen(sLine) - 1;
		if(sLine[len] == '\n') {
			sLine[len] = 0;
		} else {
			fprintf(stderr, "Error: Line too long at line %d\n", cLine);
			return -1;
		}
		printf("%d. %s\n", cLine, sLine);
		cLine++;
	}
}
