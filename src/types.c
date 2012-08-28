#include<stdio.h>
#include<stdlib.h>
#include "types.h"

ReservedWordList parseResWordFile(FILE* fp) {
	ReservedWordList list;
	ReservedWordList *hare = &list;

	while(!feof(fp)) {
		ReservedWord *rw = malloc(sizeof(ReservedWord));
		fscanf(fp, "%s %d %d", &rw->word, &rw->type, &rw->attribute);
		hare->rword = rw;
		hare->next = malloc(sizeof(ReservedWordList));
		hare = hare->next;
	}

	return list;
}
