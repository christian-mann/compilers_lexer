#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "types.h"
#include "machines.h"

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
	char sLine[80];
	int cLine = 1;
	while(fgets(sLine, sizeof(sLine), fSrc) != NULL && !feof(fSrc)) {
		int length = strlen(sLine);
		printf("%d. %s\n", cLine, sLine);
		cLine++;

		//split line into tokens
		char *psLine = sLine;
		while(psLine < sLine + length) {
			MachineResult res = identifyToken(psLine);
			if(res.validToken)
				printf("Token: '%s'\n", res.lexeme);
			else {
				printf("INVALID TOKEN OMG -- string = '%s'\n", psLine);
				break;
			}
			psLine = res.newString;
			free(res.lexeme);
		}
	}
}
