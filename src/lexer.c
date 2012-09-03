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

	//create symbol table
	SymbolTable *symbtab = malloc(sizeof(SymbolTable));

	//read in reserved word list
	ReservedWordList *rwl = malloc(sizeof(ReservedWordList));

	//begin reading a line at a time
	char sLine[80];
	int cLine = 1;
	while(fgets(sLine, sizeof(sLine), fSrc) != NULL && !feof(fSrc)) {
		int length = strlen(sLine);
		printf("%d. %s", cLine, sLine);
		cLine++;

		//split line into tokens
		char *psLine = sLine;
		while(psLine < sLine + length) {
			MachineResult res = identifyToken(psLine, rwl, symbtab);
			if(res.validToken) {
				if(res.type != TYPE_WS) { //we don't care about whitespace
					printf("Token: '%s', type: %d, attribute: %d\n", res.lexeme, res.type, res.attribute);
				}
			} else {
				printf("INVALID TOKEN OMG -- string = '%s'\n", psLine);
				break;
			}
			psLine = res.newString;
			free(res.lexeme);
		}
	}
}
