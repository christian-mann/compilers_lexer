typedef struct {
	char* lexeme;
	char* newString;
	int type;
	int attribute;
	int validToken;
} MachineResult;

MachineResult identifyToken(char* str);
typedef MachineResult (*Machine)(char*);

typedef struct {
	char* word;
} SymbolTableEntry;

typedef struct symbtab {
	SymbolTableEntry* entry;
	struct symbtab* next;
} SymbolTable;
