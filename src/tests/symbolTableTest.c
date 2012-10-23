#include<stdio.h>
#include "../types.h"
#include "../machines.c"

int main() {
	FILE *fReservedWords = fopen("../../data/reserved-words.txt", "r");
	ReservedWordList *rwl = parseResWordFile(fReservedWords);
	
	char *word = "mod";
	if(CheckReservedWords(word, rwl)) {
		printf("%s found\n", word);
	} else {
		printf("%s not found\n", word);
	}

	return 0;
}
