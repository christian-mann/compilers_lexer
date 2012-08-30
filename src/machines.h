typedef struct {
	char* lexeme;
	char* newString;
	int type;
	int attribute;
	int validToken;
} MachineResult;

MachineResult identifyToken(char* str);
typedef MachineResult (*Machine)(char*);

char* WS(char*);
