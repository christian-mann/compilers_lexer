#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "types.h"
#include "machines.h"

int main(int argc, char **argv) {
	//open the files given as an argument
	char *sfSrc, *sfListing, *sfToken, *sfSymbolTable, *sfReservedWords;
	sfSrc = sfListing = sfToken = sfSymbolTable = sfReservedWords = NULL;

	FILE *fSrc, *fListing, *fToken, *fSymbolTable, *fReservedWords;
	fSrc = fListing = fToken = fSymbolTable = fReservedWords = NULL;

	// format: ./a.out -r sfReservedWords [-l sfListing] [-t sfToken] [[-s] sfSrc]
	int i;
	for(i = 0; i < argc; i++) {
		if(!strcmp(argv[i], "-l")) {
			sfListing = argv[i+1];
		}
		if(!strcmp(argv[i], "-t")) {
			sfToken = argv[i+1];
		}
		if(!strcmp(argv[i], "-r")) {
			sfReservedWords = argv[i+1];
		}
		if(!strcmp(argv[i], "-s")) {
			sfSymbolTable = argv[i+1];
		}
		if(i == argc-1) {
			sfSrc = argv[i];
		}
	}
	if(!sfSrc || (fSrc = fopen(sfSrc, "r")) == NULL) {
		fprintf(stderr, "Warning: source file not given or not found, using stdin.\n");
		fSrc = stdin;
	}
	if(!sfToken || (fToken = fopen(sfToken, "w")) == NULL) {
		fprintf(stderr, "Warning: token file not given or not found, using stdout.\n");
		fToken = stdout;
	}
	if(!sfSymbolTable || (fSymbolTable = fopen(sfSymbolTable, "w")) == NULL) {
		fprintf(stderr, "Warning: symbol table file not given or not found, not outputting symbol table.\n");
	}
	if(!sfListing || (fListing = fopen(sfListing, "w")) == NULL) {
		fprintf(stderr, "Warning: listing file not given or not found, not outputting listing.\n");
	}


	//create symbol table
	machinesInit(sfReservedWords);

	//begin reading a line at a time
	char sLine[80];
	int cLine = 1;
	bool eof = false;
	while(!eof) {
		fgets(sLine, sizeof(sLine), fSrc);
		if(feof(fSrc)) {
			sLine[0] = EOF;
			sLine[1] = 0;
		}
		int length = strlen(sLine);
		if(fListing && !feof(fSrc)) fprintf(fListing, "%d\t%s", cLine, sLine);


		//split line into tokens
		char *psLine = sLine;
		while(psLine < sLine + length && fToken) {
			MachineResult res = identifyToken(psLine);
			if(res.type == T_WS) { //we don't care about whitespace

			} else if(res.type == T_ID) {
				fprintf(fToken, "%d\t%s\t%s\t%p\n", cLine, res.lexeme, convertConstantToString(res.type), res.pointer);
				if(res.error && fListing) {
					fprintf(fListing, "%s:\t%p:\t%s\n", convertConstantToString(res.type), res.pointer, res.lexeme);
				}
			} else if(res.type == T_EOF) {
				fprintf(fToken, "%d\t%s\t%s\t%s\n", cLine, "(EOF)", convertConstantToString(res.type), convertConstantToString(res.attribute));
				eof = true;
			} else {
				fprintf(fToken, "%d\t%s\t%s\t%s\n", cLine, res.lexeme, convertConstantToString(res.type), convertConstantToString(res.attribute));
				if(res.error && fListing) {
					fprintf(fListing, "%s:\t%s:\t%s\n", convertConstantToString(res.type), convertConstantToString(res.attribute), res.lexeme);
				}
			}
			psLine = res.newString;
			free(res.lexeme);
		}
		cLine++;
	}

	//print symbol table
	if(fSymbolTable) {
		for(SymbolTable* s = tab; s && s->entry && s->entry->word; s = s->next) {
			fprintf(fSymbolTable, "%s\t%p\n", s->entry->word, s->entry);
		}
	}
}
