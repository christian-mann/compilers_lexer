#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "types.h"
#include "machines.h"

int main(int argc, char **argv) {
	//open the files given as an argument
	char *sfSrc, *sfListing, *sfToken, *sfReservedWords;
	FILE *fSrc, *fListing, *fToken, *fReservedWords;
	sfSrc = sfListing = sfToken = NULL;

	// format: ./a.out -r sfReservedWords [-l sfListing] [-t sfToken] [[-s] sfSrc]
	int i;
	for(i = 0; i < argc; i++) {
		if(!strcmp(argv[i], "-l")) {
			sfListing = argv[i+1];
		}
		if(!strcmp(argv[i], "-t")) {
			sfToken = argv[i+1];
		}
		if(!strcmp(argv[i], "-s") || i == argc - 2) {
			sfSrc = argv[i+1];
		}
		if(!strcmp(argv[i], "-r")) {
			sfReservedWords = argv[i+1];
		}
	}
	if(!sfSrc || (fSrc = fopen(sfSrc, "r")) == NULL) {
		fprintf(stderr, "Warning: source file not given or not found, using stdin\n");
		fSrc = stdin;
	}
	if(!sfToken || (fToken = fopen(sfToken, "w")) == NULL) {
		fprintf(stderr, "Warning: token file not given or not found, using stdout\n");
		fToken = stdout;
	}
	if(!sfReservedWords || (fReservedWords = fopen(sfReservedWords, "r")) == NULL) {
		fprintf(stderr, "Warning: reserved word file not given or not found, not using reserved words\n");
	}

	//create symbol table
	SymbolTable *symbtab = malloc(sizeof(SymbolTable));

	//read in reserved word list
	ReservedWordList *rwl;
	if(fReservedWords) {
		rwl = parseResWordFile(fReservedWords);
	} else {
		rwl = malloc(sizeof(ReservedWordList));
	}

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
					printf("%s\t%s\t%s\t%s\n", res.lexeme, convertConstantToString(res.type), convertConstantToString(res.attribute), convertConstantToString(res.error));
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
