#include<stdio.h>
#include<stdlib.h>

#include "../machines.h"
#include "../types.h"

int main() {
	char *valid[] = {
		"id34567890",
		"1234567890",
		"12345.12345",
		"12345.02345",
		"12345.12345E11",
		"12345.12345E+11",
		"12345.12345E-11",
		">",
		"<",
		":=",
		" ",
		"\n",
		"if",
		"[",
		"(",
		":",
		";",
		"..",
	};
	char *invalid[] = {
		"id345678901",
		"12345678901",
		"02345678901",
		"12345.123451",
		"12345.12345E111",
		"12345.12345E+111",
		"12345.12345E-01",
	};
	char *extra[] = {
		"...",
		"12345E11",
	};

	ReservedWordList *rwl = parseResWordFile(fopen("../../data/reserved-words.txt", "r"));
	SymbolTable *s = (SymbolTable*)malloc(sizeof(SymbolTable));
	for(int i = 0; i < sizeof(valid)/sizeof(valid[0]); i++) {
		MachineResult res = identifyToken(valid[i], rwl, s);
		if(res.error || *res.newString != 0) {
			printf("Something went wrong with string %s: ", valid[i]);
			printf("{%s, %s, %d, %d, %d}\n", res.lexeme, res.newString, res.type, res.attribute, res.error);
		} else {
			//printf("%s -> %s\n", res.lexeme, convertConstantToString(res.type));
		}
	}

	for(int i = 0; i < sizeof(invalid)/sizeof(invalid[0]); i++) {
		MachineResult res = identifyToken(invalid[i], rwl, s);
		if(!res.error) {
			printf("Something went wrong with string %s: ", invalid[i]);
			printf("{%s, %s, %d, %d, %d}\n", res.lexeme, res.newString, res.type, res.attribute, res.error);
		} else {
			//printf("%s -> %s, %s\n", invalid[i], convertConstantToString(res.type), convertConstantToString(res.error));
		}
	}

	for(int i = 0; i < sizeof(extra)/sizeof(extra[0]); i++) {
		MachineResult res = identifyToken(extra[i], rwl, s);
		if(res.newString == 0) {
			printf("Something went wrong with string %s: ", extra[i]);
			printf("{%s, %s, %d, %d, %d}\n", res.lexeme, res.newString, res.type, res.attribute, res.error);
		} else {
			//printf("%s -> %s, %s\n", extra[i], res.lexeme, res.newString);
		}
	}
	printf("If no other output, all tests passed.\n");
	return 0;
}
