#include "types.h"

typedef struct {
	char* lexeme;
	char* newString;
	int type;
	int attribute;
	int validToken;
} MachineResult;


typedef struct {
	char* word;
} SymbolTableEntry;

typedef struct symbtab {
	SymbolTableEntry* entry;
	struct symbtab* next;
} SymbolTable;

MachineResult identifyToken(char* str, ReservedWordList* rwl, SymbolTable* symbtab);
typedef MachineResult (*Machine)(char*, ReservedWordList*, SymbolTable*);
