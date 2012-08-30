

typedef struct {
	char* word;
	int type;
	int attribute;
} ReservedWord;

typedef struct rwordll {
	ReservedWord* rword;
	struct rwordll* next;
} ReservedWordList;

ReservedWordList parseResWordFile(FILE* fp);


typedef struct LinkedListString {
	char* elem;
	struct LinkedListString* next;
}
