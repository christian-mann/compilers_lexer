#include<stdio.h>

#define TYPE_RELOP 100
#define TYPE_WS 101
#define TYPE_NUM 102
#define TYPE_ENDOFFILE 103
#define TYPE_ADDOP 104
#define TYPE_MULOP 105
#define TYPE_ASSIGNOP 106

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

#define MULOP_TIMES 1050
#define MULOP_DIVIDE 1051

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
