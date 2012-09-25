#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types.h"

ReservedWordList* parseResWordFile(FILE* fp) {
	ReservedWordList *list = malloc(sizeof(ReservedWordList));
	ReservedWordList *hare = list;

	char word[11];
	int type;
	int attribute;
	while(fscanf(fp, "%s %d %d", word, &type, &attribute) != EOF) {
		ReservedWord *rw = malloc(sizeof(ReservedWord));
		rw->word = malloc((strlen(word) + 1)*sizeof(char));
		strcpy(rw->word, word);
		rw->type = type;
		rw->attribute = attribute;

		hare->rword = rw;
		hare->next = malloc(sizeof(ReservedWordList));
		hare->next->rword = NULL;
		hare = hare->next;
	}
	return list;
}

char* convertConstantToString(int constant) {
	if(constant < 50 && constant > 0) return "RWORD";
	switch(constant) {
	case TYPE_RELOP: return "TYPE_RELOP";
	case TYPE_WS: return "TYPE_WS";
	case TYPE_NUM: return "TYPE_NUM";
	case TYPE_ENDOFFILE: return "TYPE_ENDOFFILE";
	case TYPE_ADDOP: return "TYPE_ADDOP";
	case TYPE_MULOP: return "TYPE_MULOP";
	case TYPE_ASSIGNOP: return "TYPE_ASSIGNOP";
	case TYPE_PAREN: return "TYPE_PAREN";
	case TYPE_OTHER: return "TYPE_OTHER";
	case TYPE_ID: return "TYPE_ID";
	case TYPE_LEXERR: return "TYPE_LEXERR";
	case TYPE_PROGRAM: return "TYPE_PROGRAM";
	case TYPE_VAR: return "TYPE_VAR";
	case TYPE_ARRAY: return "TYPE_ARRAY";
	case TYPE_OF: return "TYPE_OF";
	case TYPE_INTEGER: return "TYPE_INTEGER";
	case TYPE_REAL: return "TYPE_REAL";
	case TYPE_FUNCTION: return "TYPE_FUNCTION";
	case TYPE_PROCEDURE: return "TYPE_PROCEDURE";
	case TYPE_BEGIN: return "TYPE_BEGIN";
	case TYPE_END: return "TYPE_END";
	case TYPE_IF: return "TYPE_IF";
	case TYPE_THEN: return "TYPE_THEN";
	case TYPE_ELSE: return "TYPE_ELSE";
	case TYPE_WHILE: return "TYPE_WHILE";
	case TYPE_DO: return "TYPE_DO";
	case TYPE_NOT: return "TYPE_NOT";
	case RELOP_EQ: return "RELOP_EQ";
	case RELOP_GE: return "RELOP_GE";
	case RELOP_GT: return "RELOP_GT";
	case RELOP_LE: return "RELOP_LE";
	case RELOP_NE: return "RELOP_NE";
	case RELOP_LT: return "RELOP_LT";
	case NUM_INT: return "NUM_INT";
	case NUM_REAL: return "NUM_REAL";
	case NUM_LONGREAL: return "NUM_LONGREAL";
	case ADDOP_PLUS: return "ADDOP_PLUS";
	case ADDOP_MINUS: return "ADDOP_MINUS";
	case ADDOP_OR: return "ADDOP_OR";
	case MULOP_TIMES: return "MULOP_TIMES";
	case MULOP_DIVIDE: return "MULOP_DIVIDE";
	case MULOP_DIV: return "MULOP_DIV";
	case MULOP_MOD: return "MULOP_MOD";
	case MULOP_AND: return "MULOP_AND";
	case PAREN_OPEN: return "PAREN_OPEN";
	case PAREN_CLOSE: return "PAREN_CLOSE";
	case OTHER_COMMA: return "OTHER_COMMA";
	case OTHER_SEMICOLON: return "OTHER_SEMICOLON";
	case OTHER_COLON: return "OTHER_COLON";
	case OTHER_PERIOD: return "OTHER_PERIOD";
	case ERR_ID_LEN: return "ERR_ID_LEN";
	case ERR_INT_LEN: return "ERR_INT_LEN";
	case ERR_INT_LEADING_ZERO: return "ERR_INT_LEADING_ZERO";
	case ERR_DECIMAL_LEN: return "ERR_DECIMAL_LEN";
	case ERR_EXPONENT_LEN: return "ERR_EXPONENT_LEN";
	case ERR_EXPONENT_LEADING_ZERO: return "ERR_EXPONENT_LEADING_ZERO";
	case 0: return "NULL";
	}
	//symbol pointers
	char *str = malloc(40*sizeof(char)); //that should be more than sufficient
	sprintf(str, "%p", constant);
	return str;
}
