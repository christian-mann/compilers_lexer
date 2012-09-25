#include<stdio.h>

#ifndef TYPES_H
#define TYPES_H

#define TYPE_RELOP 100
#define TYPE_WS 101
#define TYPE_NUM 102
#define TYPE_ENDOFFILE 103
#define TYPE_ADDOP 104
#define TYPE_MULOP 105
#define TYPE_ASSIGNOP 106
#define TYPE_PAREN 107
#define TYPE_OTHER 108
#define TYPE_ID 109
#define TYPE_LEXERR 200
#define TYPE_PROGRAM 300
#define TYPE_VAR 301
#define TYPE_ARRAY 302
#define TYPE_OF 303
#define TYPE_INTEGER 304
#define TYPE_REAL 305
#define TYPE_FUNCTION 306
#define TYPE_PROCEDURE 307
#define TYPE_BEGIN 308
#define TYPE_END 309
#define TYPE_IF 310
#define TYPE_THEN 311
#define TYPE_ELSE 312
#define TYPE_WHILE 313
#define TYPE_DO 314
#define TYPE_NOT 315

#define RELOP_EQ 1000
#define RELOP_GE 1001
#define RELOP_GT 1002
#define RELOP_LE 1003
#define RELOP_NE 1004
#define RELOP_LT 1005

#define NUM_INT 1020
#define NUM_REAL 1021
#define NUM_LONGREAL 1022

#define ADDOP_PLUS 1040
#define ADDOP_MINUS 1041
#define ADDOP_OR 1042

#define MULOP_TIMES 1050
#define MULOP_DIVIDE 1051
#define MULOP_DIV 1052
#define MULOP_MOD 1053
#define MULOP_AND 1054

#define PAREN_OPEN 1070
#define PAREN_CLOSE 1071

#define OTHER_COMMA 1080
#define OTHER_SEMICOLON 1081
#define OTHER_COLON 1082
#define OTHER_PERIOD 1083

#define ERR_ID_LEN 2000
#define ERR_INT_LEN 2001
#define ERR_INT_LEADING_ZERO 2002
#define ERR_DECIMAL_LEN 2003
#define ERR_EXPONENT_LEN 2004
#define ERR_EXPONENT_LEADING_ZERO 2005

typedef struct {
	char* word;
	int type;
	int attribute;
} ReservedWord;

typedef struct rwordll {
	ReservedWord* rword;
	struct rwordll* next;
} ReservedWordList;

ReservedWordList* parseResWordFile(FILE* fp);
char* convertConstantToString(int);

#endif
