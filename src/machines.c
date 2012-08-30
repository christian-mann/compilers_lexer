#include<stdlib.h>
#include<string.h>
#include "machines.h"
#include "types.h"
MachineResult IDRES(char* str) {
	char* b = str;
	char* f = b;
	int state = 0;
	MachineResult res;
	while(*f) {
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
			res.type = res.attribute = -1;
			res.validToken = 0;
			return res;
		}
		
		//increment forward pointer
		f++;
	}
}

MachineResult RELOP(char* str) {
	char* f = str;
	int state = 0;
	MachineResult res;
	while(*f) {
		switch(state) {
		case 0:
			if(*f == '>') state = 1;
			if(*f == '<') state = 2;
			if(*f == '=') state = 3;
			else state = -1;
			break;
		case 1:
			if(*f == '=') state = 4;
			else state = 5;
			break;
		case 2:
			if(*f == '=') state = 6;
			if(*f == '>') state = 7;
			else state = 8;
			break;
		case 3:
			res.type = RELOP_EQ;
			break;
		case 4:
			res.type = RELOP_GE;
			break;
		case 5:
			res.type = RELOP_GT;
			break;
		case 6:
			res.type = RELOP_LE;
			break;
		case 7:
			res.type = RELOP_NE;
			break;
		case 8:
			res.type = RELOP_LT;
			break;
		case -1:
			res.validToken = 0;
			res.newString = str;
			res.type = res.attribute = -1;
			return res;
		}
		f++;
	}
	if(f > str) {
		res.validToken = 1;
		res.type = TYPE_RELOP;
		res.newString = f;
	} else {
		res.validToken = 0;
		res.newString = str;
		res.type = res.attribute = -1;
	}
	return res;
}

MachineResult WS(char* str) {
	char* f = str;
	if(*f == ' ' || *f == '\n' || *f == '\t') {
		while(*f == ' ' || *f == '\n' || *f == '\t')
			f++;
		f--;
		MachineResult res;
		res.type = TYPE_WS;
		res.newString = f;
		res.validToken = 0;
		return res;
	} else {
		MachineResult res;
		res.newString = str;
		res.type = res.attribute = 0;
		res.validToken = 0;
		return res;
	}
	
}

MachineResult INT(char* str) {
	char* f = str;
	int state = 0;
	while(*f) {
		switch(state) {
			case 0:
				if('0' <= *f <= '9')
					state = 1;
				else
					state = -1;
				break;
			case 1:
				if('0' <= *f <= '9')
					state = 1;
				else
					state = 2;
				break;
			case 2:
				f--;
				MachineResult res;
				res.newString = f;
				res.type = TYPE_NUM;
				res.attribute = NUM_INT;
				res.validToken = 1;
				return res;
		}
		f++;
	}
}

MachineResult REAL(char* str) {
	char* f = str;
	int state = 0;
	while(*f) {
		switch(state) {
			case 0:
				if('0' <= *f <= '9')
					state = 1;
				else
					state = -1;
				break;
			case 1:
				if('0' <= *f <= '9')
					state = 1;
				else if (*f == '.')
					state = 2;
				else
					state = -1;
			case 2:
				if('0' <= *f <= '9')
					state = 3;
				else
					state = -1;
			case 3:
				if('0' <= *f <= '9')
					state = 3;
				else
					state = 4;
			case 4:
				f--;
				MachineResult res;
				res.newString = f;
				res.type = TYPE_NUM;
				res.attribute = NUM_REAL;
				res.validToken = 1;
				return res;
		}
		f++;
	}
}

MachineResult LONGREAL(char* str) {
	char* f = str;
	int state = 0;
	while(*f) {
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
			case 5:
				if('1' <= *f && *f <= '9')
					state = 6;
				else
					state = -1;
			case 6:
				if('1' <= *f && *f <= '9')
					state = 6;
				else
					state = 7;
			case 7:
				f--;
				MachineResult res;
				res.newString = f;
				res.type = TYPE_NUM;
				res.attribute = NUM_LONGREAL;
				res.validToken = 1;
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
