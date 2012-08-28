#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<file.h>

#define NULL 0

int main(int argc, char **argv) {
	//open the file given as an argument
	char *sfSrc;
	FILE *fSrc;
	if(argc > 1) {
		sfSrc = argv[1];
		if(!(fSrc = fopen(sfSrc, "r"))) {
			fprintf("No source file found at %s", sfSrc);
		}
	} else {
		fprintf("Warning: No source file given; using stdin", stderr);
		fSrc = stdin;
	}

	//begin reading a line at a time
	char sLine[73];
	int cLine = 1;
	while(fgets(sLine, sizeof(sLine)-1, fSrc) != NULL) {
		//strip trailing '\n' if it exists
		int len = strlen(sLine) - 1;
		if(sLine[len] == '\n')
			sLine[len] = 0;
		printf("%d. %s\n", cLine, sLine);
		cLine++;
	}
}
