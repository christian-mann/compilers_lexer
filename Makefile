bin/lexer: src/lexer.c
	mkdir -p bin
	gcc src/lexer.c -o bin/lexer
