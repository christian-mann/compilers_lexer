all:
	gcc -Wall -g -std=c99 src/*.c -o bin/lexer

clean:
	rm -f bin/*
