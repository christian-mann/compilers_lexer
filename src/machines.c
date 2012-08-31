#include<stdlib.h>
#include<string.h>
#include "machines.h"
#include "types.h"
MachineResult IDRES(char* str) {
	char* b = str;
	char* f = b;
	int state = 0;
	MachineResult res;
	while(1) {
		switch(state) {
		case 0:
			if('a' <= *f && *f <= 'z' || 'A' <= *f && *f <= 'Z')
				state = 1;
			else {
				res.newString = str;
				res.type = -1;
				res.attribute = -1;
				res.validToken = 0;
				return res;
			}
			break;
		case 1:
			if('a' <= *f && *f <= 'z' || 'A' <= *f && *f <= 'Z' || '0' <= *f && *f <= '9')
				state = 1;
			else
				state = 2;
			break;
		case 2:
			//valid identifier
			//Decrement forward pointer, since we consumed a character we shouldn't have
			f--;
			res.newString = f;
			res.type = res.attribute = -2; //TODO get from list
			res.validToken = 1;
			return res;
		}
		//increment forward pointer
		f++;
	}
}

ReservedWord* CheckReservedWords(char* word, ReservedWordList* rwl) {
	//Search for word in rwl
	while(rwl != NULL) {
		if(!strcmp(word, rwl->rword->word)) {
			//found it!
			return rwl->rword;
		} else {
			//go to next link
			rwl = rwl->next;
		}
	}
	return NULL;
}

//SymbolTableEntry* checkSymbolTable(char* word, SymbolTable* tab) {
//	while(tab != NULL) {
//		if(!strcmp(word, tab->entry->word)) {
//			//found it!
//			return tab->entry;
//		} else {
//			//go to next link
//			tab = tab->next;
//		}
//	}
//}

MachineResult RELOP(char* str) {
	char* f = str;
	int state = 0;
	MachineResult res;
	res.validToken = 1;
	res.type = TYPE_RELOP;
	res.newString = f;
	while(1) {
		switch(state) {
		case 0:
			state = -1;
			if(*f == '>') state = 1;
			if(*f == '<') state = 2;
			if(*f == '=') state = 3;
			break;
		case 1:
			state = 5;
			if(*f == '=') state = 4;
			break;
		case 2:
			state = 8;
			if(*f == '=') state = 6;
			if(*f == '>') state = 7;
			break;
		case 3:
			res.attribute = RELOP_EQ;
			res.newString = f;
			return res;
		case 4:
			res.attribute = RELOP_GE;
			res.newString = f;
			return res;
		case 5:
			res.attribute = RELOP_GT;
			res.newString = f;
			return res;
		case 6:
			res.attribute = RELOP_LE;
			res.newString = f;
			return res;
		case 7:
			res.attribute = RELOP_NE;
			res.newString = f;
			return res;
		case 8:
			res.attribute = RELOP_LT;
			res.newString = f;
			return res;
		case -1:
			res.validToken = 0;
			res.newString = str;
			res.type = res.attribute = -1;
			return res;
		}
		f++;
	}
}

MachineResult WS(char* str) {
	char* f = str;
	int state = 0;
	MachineResult res;
	while(1) {
		switch(state) {
			case 0:
				if(*f == ' ' || *f == '\n' || *f == '\t' || *f == '\r')
					state = 1;
				else
					state = -1;
				break;
			case 1:
				if(*f == ' ' || *f == '\n' || *f == '\t' || *f == '\r')
					state = 1;
				else
					state = 2;
				break;
			case 2:
				f--;
				res.newString = f;
				res.type = TYPE_WS;
				res.attribute = 0;
				res.validToken = 1;
				return res;
			case -1:
				res.newString = str;
				res.type = res.attribute = -1;
				res.validToken = 0;
				return res;
		}
		f++;
	}
}

MachineResult INT(char* str) {
	char* f = str;
	int state = 0;
	MachineResult res;
	while(1) {
		switch(state) {
			case 0:
				if('0' <= *f && *f <= '9')
					state = 1;
				else
					state = -1;
				break;
			case 1:
				if('0' <= *f && *f <= '9')
					state = 1;
				else {
					state = 2;
				}
				break;
			case 2:
				f--;
				res.newString = f;
				res.type = TYPE_NUM;
				res.attribute = NUM_INT;
				res.validToken = 1;
				return res;
			case -1:
				res.newString = str;
				res.type = -1;
				res.attribute = -1;
				res.validToken = 0;
				return res;
		}
		f++;
	}
}

MachineResult REAL(char* str) {
	char* f = str;
	int state = 0;
	MachineResult res;
	while(1) {
		switch(state) {
			case 0:
				if('0' <= *f && *f <= '9')
					state = 1;
				else
					state = -1;
				break;
			case 1:
				if('0' <= *f && *f <= '9')
					state = 1;
				else if (*f == '.')
					state = 2;
				else
					state = -1;
				break;
			case 2:
				if('0' <= *f && *f <= '9')
					state = 3;
				else
					state = -1;
				break;
			case 3:
				if('0' <= *f && *f <= '9')
					state = 3;
				else
					state = 4;
				break;
			case 4:
				f--;
				res.newString = f;
				res.type = TYPE_NUM;
				res.attribute = NUM_REAL;
				res.validToken = 1;
				return res;
			case -1:
				res.newString = str;
				res.type = -1;
				res.attribute = -1;
				res.validToken = 0;
				return res;
		}
		f++;
	}
}

MachineResult LONGREAL(char* str) {
	char* f = str;
	int state = 0;
	MachineResult res;
	while(1) {
		switch(state) {
			case 0:
				if('0' <= *f && *f <= '9')
					state = 1;
				else
					state = -1;
				break;
			case 1:
				if('0' <= *f && *f <= '9')
					state = 1;
				else if (*f == '.')
					state = 2;
				else
					state = -1;
				break;
			case 2:
				if('0' <= *f && *f <= '9')
					state = 3;
				else
					state = -1;
				break;
			case 3:
				if('0' <= *f && *f <= '9')
					state = 3;
				else if (*f == 'E')
					state = 4;
				else
					state = -1;
				break;
			case 4:
				if(*f == '+' || *f == '-')
					state = 5;
				else if('1' <= *f && *f <= '9')
					state = 6;
				else
					state = -1;
				break;
			case 5:
				if('1' <= *f && *f <= '9')
					state = 6;
				else
					state = -1;
				break;
			case 6:
				if('1' <= *f && *f <= '9')
					state = 6;
				else
					state = 7;
				break;
			case 7:
				f--;
				res.newString = f;
				res.type = TYPE_NUM;
				res.attribute = NUM_LONGREAL;
				res.validToken = 1;
				return res;
			case -1:
				res.newString = str;
				res.type = -1;
				res.attribute = -1;
				res.validToken = 0;
				return res;
		}
		f++;
	}
}

MachineResult ENDOFFILE(char* str) {
	MachineResult res;
	res.type = TYPE_ENDOFFILE;
	res.attribute = 0;
	res.validToken = 1;
	if(*str == 4) {//end-of-file character
		res.newString = str+1;
	} else {
		res.newString = str;
		res.validToken = 0;
	}
	return res;
}

MachineResult CATCHALL(char* str) {
	MachineResult res;
	res.validToken = 1;
	res.newString = str+1;
	switch(*str) {
		case '(':
			res.type = TYPE_PAREN;
			res.attribute = PAREN_OPEN;
			return res;
		case ')':
			res.type = TYPE_PAREN;
			res.attribute = PAREN_CLOSE;
			return res;
		case ',':
			res.type = TYPE_OTHER;
			res.attribute = OTHER_COMMA;
			return res;
		case ';':
			res.type = TYPE_OTHER;
			res.attribute = OTHER_SEMICOLON;
			return res;
		case '.':
			res.type = TYPE_OTHER;
			res.attribute = OTHER_PERIOD;
			return res;
		case '+':
			res.type = TYPE_ADDOP;
			res.attribute = ADDOP_PLUS;
			return res;
		case '-':
			res.type = TYPE_ADDOP;
			res.attribute = ADDOP_MINUS;
			return res;
		case '*':
			res.type = TYPE_MULOP;
			res.attribute = MULOP_TIMES;
			return res;
		case '/':
			res.type = TYPE_MULOP;
			res.attribute = MULOP_DIVIDE;
			return res;
		case ':':
			if(str[1] == '=') {
				res.type = TYPE_ASSIGNOP;
				res.attribute = 0;
				res.newString = str+2;
				return res;
			} else {
				res.type = TYPE_OTHER;
				res.attribute = OTHER_COLON;
				return res;
			}
	}
	res.validToken = 0;
	res.type = res.attribute = -1;
	res.newString = str;
	return res;
}


static Machine machines[] = {&WS, &IDRES, &LONGREAL, &REAL, &INT, &RELOP, &CATCHALL, &ENDOFFILE};

MachineResult identifyToken(char* str) {
	int i;
	for(i = 0; i < sizeof(machines)/sizeof(machines[0]); i++) {
		MachineResult res = machines[i](str);
		if(res.validToken) {
			int size = res.newString - str;
			res.lexeme = malloc(size*sizeof(char)+1);
			memcpy(res.lexeme, str, size);
			res.lexeme[size] = 0;
			return res;
		}
	}
	//unrecognized token
	MachineResult res;
	res.lexeme = NULL;
	res.newString = str;
	res.type = res.attribute = -1;
	res.validToken = 0;
	return res;
}
