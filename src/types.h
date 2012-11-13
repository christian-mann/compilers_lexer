#include<stdio.h>

#ifndef TYPES_H
#define TYPES_H

#ifndef X
#define TYPES_H_DEFINED_X
#define X(a, b) a b,
#endif

#define SYMBS \
X(NULL_, =0) \
X(TYPE_RELOP, ) \
X(TYPE_WS, ) \
X(TYPE_NUM, ) \
X(TYPE_ENDOFFILE, ) \
X(TYPE_ADDOP, =104) \
X(TYPE_MULOP, =105) \
X(TYPE_ASSIGNOP, ) \
X(TYPE_PAREN, ) \
X(TYPE_COMMA, ) \
X(TYPE_SEMICOLON, ) \
X(TYPE_COLON, ) \
X(TYPE_PERIOD, ) \
X(TYPE_DOUBLEPERIOD, ) \
X(TYPE_ID, ) \
X(TYPE_LBRACK, ) \
X(TYPE_RBRACK, ) \
X(TYPE_LPAREN, ) \
X(TYPE_RPAREN, ) \
X(TYPE_LEXERR, ) \
X(TYPE_PROGRAM, =300) \
X(TYPE_VAR, =301) \
X(TYPE_ARRAY, =302) \
X(TYPE_OF, =303) \
X(TYPE_INTEGER, =304) \
X(TYPE_REAL, =305) \
X(TYPE_FUNCTION, =306) \
X(TYPE_PROCEDURE, =307) \
X(TYPE_BEGIN, =308) \
X(TYPE_END, =309) \
X(TYPE_IF, =310) \
X(TYPE_THEN, =311) \
X(TYPE_ELSE, =312) \
X(TYPE_WHILE, =313) \
X(TYPE_DO, =314) \
X(TYPE_NOT, =315) \
X(RELOP_EQ, ) \
X(RELOP_GE, ) \
X(RELOP_GT, ) \
X(RELOP_LE, ) \
X(RELOP_NE, ) \
X(RELOP_LT, ) \
X(NUM_INT, ) \
X(NUM_REAL, ) \
X(NUM_LONGREAL, ) \
X(ADDOP_PLUS, ) \
X(ADDOP_MINUS, ) \
X(ADDOP_OR, =1042) \
X(MULOP_TIMES, ) \
X(MULOP_DIVIDE, ) \
X(MULOP_DIV, =1052) \
X(MULOP_MOD, =1053) \
X(MULOP_AND, =1054) \
X(ERR_ID_LEN, ) \
X(ERR_INT_LEN, ) \
X(ERR_INT_LEADING_ZERO, ) \
X(ERR_DECIMAL_LEN, ) \
X(ERR_EXPONENT_LEN, ) \
X(ERR_EXPONENT_LEADING_ZERO, ) \
X(ERR_UNRECOG_TOKEN, ) \

#ifdef TYPES_H_DEFINED_X

enum Symbol {
	SYMBS
};

#undef X
#undef TYPES_H_DEFINED_X
#endif

typedef struct rword {
	char* word;
	enum Symbol type;
	enum Symbol attribute;
} ReservedWord;

typedef struct rwordll {
	ReservedWord* rword;
	struct rwordll* next;
} ReservedWordList;

ReservedWordList* parseResWordFile(FILE* fp);
char* convertConstantToString(enum Symbol);

#endif
