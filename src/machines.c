#include<machines.h>
char* IDRES(char* str) {
	char* b = str;
	char* f = b;
	int state = 0;
	while(*f) {
		switch(state) {
		case 0:
			if('a' <= *f && *f <= 'z' || 'A' <= *f && *f <= 'Z')
				state = 1;
			else
				return b; //*false?
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
			return f;
			break;
		}
		
		//increment forward pointer
		f++;
	}
	//We reached end of string.
	return b; //false?
}

char* RELOP(char* str) {
	char* f = str;
	int state = 0;
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
			//RELOP, EQ
			return f;
			break;
		case 4:
			//RELOP, GE
			return f;
			break;
		case 5:
			//RELOP, GT
			return f;
			break;
		case 6:
			//RELOP, LE
			return f;
			break;
		case 7:
			//RELOP, NE
			return f;
			break;
		case 8:
			//RELOP, LT
			return f;
			break;
		case -1:
			//error case
			return b; //false?
		}
		f++;
	}
	return b;
}

char* WS(char* str) {
	if(*str == ' ' || *str == '\n' || *str == '\t')
		while(*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	return str;
}

char* INT(char* str) {
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
				return; //NUM, INT
		}
		f++;
	}
}

char* REAL(char* str) {
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
				return; //NUM, REAL
		}
		f++;
	}
}

char* LONGREAL(char* str) {
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
				return f; //NUM, LONGREAL
		}
		f++;
	}
}

char* ENDOFFILE(char* str) {
	if(*str == 4) //end-of-file character
		return str+1;
	else
		return str;
}

char* CATCHALL(char* str) {
	switch(*str) {
		case '+':
			//ADDOP, PLUS
		case '-':
			//ADDOP, MINUS
		case '*':
			//MULOP, TIMES
		case '/':
			//MULOP, DIVIDE
		case ':':
			if(str[1] == '=')
				//ASSIGNOP, NULL
				1+1;
	}
}

typedef MachineResult (*machineArr[])(char*) MachineArray;

static MachineArray machines = {&WS, &IDRES, &LONGREAL, &REAL, &INT, &RELOP, &CATCHALL, &ENDOFFILE};

MachineResult identifyToken(char* str) {
	for(int i = 0; i < sizeof(machines)/sizeof(machines[0]); i++) {
		MachineResult res = machines[i](str);
		if(res.validToken)
			return res;
	}
	//unrecognized token
}
